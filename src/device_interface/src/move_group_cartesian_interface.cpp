#include "ros/ros.h"
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

void robot_move_group_interface(geometry_msgs::Pose& msg)
{
  float x, y, z;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;

  z = msg.position.z * 0.004;
  y = msg.position.y * 0.004;
  x = msg.position.x * 0.004;


  std::vector<geometry_msgs::Pose> waypoints;
  moveit::planning_interface::MoveGroupInterface::Plan cartesian_plan;
  robot_state::RobotState start_state(*move_group.getCurrentState());
  geometry_msgs::Pose target_pose = move_group.getCurrentPose().pose;
  robot_state::JointModelGroup *joint_model_group = start_state.getJointModelGroup(move_group.getName());
  group.setStartState(start_state)
  target_pose.position.z = z;
  waypoints.push_back(target_pose);  // up

  target_pose.position.y = y;
  waypoints.push_back(target_pose);  // left

  target_pose.position.x = x;
  waypoints.push_back(target_pose);  // down and right

  moveit_msgs::RobotTrajectory trajectory;
  double fraction = group.computeCartesianPath(waypoints, 0.01, 0.0, trajectory);

  cartesian_plan.trajectory_ = trajectory;

  visual_tools.deleteAllMarkers();
  visual_tools.publishAxisLabeled(target_pose, "pose");
  visual_tools.publishTrajectoryLine(cartesian_plan.trajectory_, joint_model_group);
  visual_tools.publishPath(waypoints, rvt::LIME_GREEN, rvt::SMALL);
  for (std::size_t i = 0; i < waypoints.size(); ++i)
    visual_tools.publishAxisLabeled(waypoints[i], "pt" + std::to_string(i), rvt::SMALL);

  visual_tools.trigger();

  ROS_INFO("Visualizing plan - cartesian path (%.2f%% acheived)", fraction * 100.0);
/* Sleep to give Rviz time to visualize the plan. */
  sleep(15.0);
  /* Uncomment below line when working with a real robot */
  //move_group.move();
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::Subscriber sub = node_handle.subscribe("pubDeviceOut", 1, robot_move_group_interface);
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  static const std::string PLANNING_GROUP = "manipulator";

  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);

  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

  const robot_state::JointModelGroup *joint_model_group = move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  namespace rvt = rviz_visual_tools;

  moveit_visual_tools::MoveItVisualTools visual_tools("odom_combined");
  visual_tools.deleteAllMarkers();
  visual_tools.loadRemoteControl();

  Eigen::Affine3d text_pose = Eigen::Affine3d::Identity();
  text_pose.translation().z() = 2.1; // above robot
  visual_tools.publishText(text_pose, "MoveGroupInterface Demo", rvt::WHITE, rvt::XLARGE);

  visual_tools.trigger();
  ROS_INFO_NAMED("tutorial", "Reference frame: %s", move_group.getPlanningFrame().c_str());
  ROS_INFO_NAMED("tutorial", "End effector link: %s", move_group.getEndEffectorLink().c_str());

  //ros::shutdown();
  return 0;
}
