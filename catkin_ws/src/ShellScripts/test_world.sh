#!/bin/sh
CATKIN_DIR=/home/workspace/home_service_robot/catkin_ws
echo "$CATKIN_DIR"

xterm  -e  " source $CATKIN_DIR/devel/setup.bash; roscore" & 
sleep 5
xterm  -e  " source $CATKIN_DIR/devel/setup.bash; roslaunch home_service_bot MyWorld.launch "
sleep 5


xterm  -e  " source $CATKIN_DIR/devel/setup.bash; rosservice call /gazebo/set_model_state '{model_state: { model_name: mobile_base, pose: { position: { x: 5.0, y: 8.75, z: 0 }, orientation: {x: 0, y: 0, z: -0.676, w: 0.737}}}}'" 
