#!/bin/bash

echo "==== Hardware ===="
ros2 control list_hardware_components

echo
echo "==== Controllers ===="
ros2 control list_controllers

echo
echo "==== Interfaces ===="
ros2 control list_hardware_interfaces

echo
echo "==== Nodes ===="
ros2 node list

echo
echo "==== Joint States ===="
ros2 topic hz /joint_states
