#!/bin/sh
xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5
xterm  -e  "roslaunch gazebo /src/home_service_bot/worlds/MyWorld.world" 

