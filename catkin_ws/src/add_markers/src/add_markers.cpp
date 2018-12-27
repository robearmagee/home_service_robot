#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "std_msgs/String.h"

  ros::Publisher marker_pub;
  // subscribe to the pick_objects zone published messages
  ros::Subscriber zone_publish;

  // publishing markers for rviz
  visualization_msgs::Marker marker;


  //interrupt when message arrives
  void goal_interrupt(const std_msgs::String::ConstPtr& msg)
  {
    //output message to terminal
    ROS_INFO("Message received: [%s]", msg->data.c_str());
    
    if (msg->data == "pick-up")
    {
      // object to be removed as it has been picked up:
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
    }
    if (msg->data == "drop-off")
    {
      // make object appear in goal_2 location
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = -4.0;
      marker.pose.position.y = 1.5;
      marker.pose.orientation.z = 0.0;
      marker.pose.orientation.w = 1.0;
      
      // Set the scale of the marker -- 1x1x1 here means 1m on a side
      marker.scale.x = 0.3;
      marker.scale.y = 0.3;
      marker.scale.z = 0.3;
      
      // Set the color -- be sure to set alpha to something non-zero!
      marker.color.r = 0.0f;
      marker.color.g = 1.0f;
      marker.color.b = 0.0f;
      marker.color.a = 1.0;
      
      marker.lifetime = ros::Duration();
      
      marker_pub.publish(marker);
    }
  }
  
  
  int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  zone_publish = n.subscribe("zone_msg", 10, goal_interrupt);
  
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  while (ros::ok())
  {
    

    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 4;
    marker.pose.position.y = 4.5;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);

    ROS_INFO("Marker showing up at the pick-up location...");
    //ros::Duration(30.0).sleep();
         
    

    //spin ROS while waiting
    ros::spin();
    //r.sleep();
  }
}
