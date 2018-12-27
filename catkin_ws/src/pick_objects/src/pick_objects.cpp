#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "std_msgs/String.h"

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

//TODO: include publisher to advise when reaching pickup and dropoff zones.
ros::Publisher zone_publish;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  
  // initialise publishing 
  ros::NodeHandle n;
  zone_publish = n.advertise<std_msgs::String>("zone_msg", 10);
  std_msgs::String msg;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal_1;
  move_base_msgs::MoveBaseGoal goal_2;

// ----------------
// Pick up location

  // set up the frame parameters
  goal_1.target_pose.header.frame_id = "map";
  goal_1.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  //goal.target_pose.pose.position.x = 1.0;
  //goal.target_pose.pose.orientation.w = 1.0;
  goal_1.target_pose.pose.position.x = 4.0;
  goal_1.target_pose.pose.position.y = 4.5;
  goal_1.target_pose.pose.orientation.z = 0.0;
  goal_1.target_pose.pose.orientation.w = 1.0;
  
  
   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal one pick-up info");
  ac.sendGoal(goal_1);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
    ROS_INFO("Hooray, the base reached the pick-up location..");

  	// TODO: Send info in msg form saying picked up/succeeded
    msg.data = "pick-up";
    zone_publish.publish(msg);
  }
  
  else {
    ROS_INFO("The base failed to move for some reason");
    return 0;
  }

 ROS_INFO("Pausing to pick_up object..");
 ros::Duration(5.0).sleep();

//----------------------
  // Drop-off location.
  
  // set up the frame parameters for goal_2
  goal_2.target_pose.header.frame_id = "map";
  goal_2.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  //goal.target_pose.pose.position.x = 1.0;
  //goal.target_pose.pose.orientation.w = 1.0;
  goal_2.target_pose.pose.position.x = -4.0;
  goal_2.target_pose.pose.position.y = 1.5;
  goal_2.target_pose.pose.orientation.z = 0.0;
  goal_2.target_pose.pose.orientation.w = 1.0;
  
   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal two drop-off info");
  ac.sendGoal(goal_2);
  
  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
{
    ROS_INFO("Hooray, the base moved to the drop-off location");
  	// TODO: Send info in msg form saying picked up/succeeded
    msg.data = "drop-off";
  	zone_publish.publish(msg);
}
  else{
    ROS_INFO("The base failed to achieve the objective.");
}

 ROS_INFO("Goal reached! Object delivered.");
 ros::Duration(15.0).sleep();
  
  return 0;
}
