#!/bin/sh

CATKIN_DIR=/home/workspace/home_service_robot/catkin_ws
echo "$CATKIN_DIR"

xterm  -e  " source $CATKIN_DIR/devel/setup.bash; roscore" &  # works ok
sleep 5
xterm  -e  " source $CATKIN_DIR/devel/setup.bash; roslaunch home_service_bot MyWorld.launch " & 
sleep 6
#xterm  -e  " source $CATKIN_DIR/devel/setup.bash; rosservice call /gazebo/set_model_state '{model_state: { model_name: mobile_base, pose: { position: { x: 5.0, y: -8.75 ,z: 0.01 } , orientation: {x: 0., y: 0., z: 0., w: 1.0}}}}'" &
sleep 6
xterm  -e  " source $CATKIN_DIR/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/home_service_robot/catkin_ws/src/home_service_bot/worlds/myMapDoors.yaml" & 

#defaults to: <arg name="map_file" default="$(find turtlebot_navigation)/maps/mapkobuki.yaml"/>
sleep 8
xterm  -e  " source $CATKIN_DIR/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch " & # ok
sleep 7

#xterm  -e  " source $CATKIN_DIR/devel/setup.bash; rosrun wall_follower wall_follower_node "
xterm  -e  " source $CATKIN_DIR/devel/setup.bash; rosrun pick_objects pick_objects_node "

# ----- xterm  -e  " source $CATKIN_DIR/devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch " 

