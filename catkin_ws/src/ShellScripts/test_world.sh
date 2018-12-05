#!/bin/sh
xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5
xterm  -e  "rosrun gazebo /src/home_service_bot/world/MyWorld/MyWorld.world" 

