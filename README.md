# robo_nd_project2
Project #2: Go Chase It!

# Setup
## Create workspace
cd ./catkin_ws/src
catkin_init_workspace

## Create my_robot package
catkin_create_pkg my_robot

## World Setup
mkdir launch
mkdir worlds
touch empty.world
### Add to empty.world
<?xml version="1.0" ?>

<sdf version="1.4">

  <world name="default">

    <include>
      <uri>model://ground_plane</uri>
    </include>

    <!-- Light source -->
    <include>
      <uri>model://sun</uri>
    </include>

    <!-- World camera -->
    <gui fullscreen='0'>
      <camera name='world_camera'>
        <pose>4.927360 -4.376610 3.740080 0.000000 0.275643 2.356190</pose>
        <view_controller>orbit</view_controller>
      </camera>
    </gui>

  </world>
</sdf>
### World Launch
gedit ./myrobot/launch/world.launch

<?xml version="1.0" encoding="UTF-8"?>

<launch>

  <!-- World File -->
  <arg name="world_file" default="$(find my_robot)/worlds/empty.world"/>

  <!-- Launch Gazebo World -->
  <include file="$(find gazebo_ros)/launch/empty_world.launch">
    <arg name="use_sim_time" value="true"/>
    <arg name="debug" value="false"/>
    <arg name="gui" value="true" />
    <arg name="world_name" value="$(arg world_file)"/>
  </include>

</launch>

### Test Empty World
cd /home/robond/projects/robo_nd_project2/catkin_ws
catkin_make
source devel/setup.bash
roslaunch my_robot world.launch

## Setup xacro file
### Add wheels
### Add sensors

## Setup Gazebo Plugins
### Setup motion controller and sensor nodes using built-in plugins


## RViz

### Run
#### Separate Window
roscore

#### Separate Window
rosrun rviz rviz

### Add Robot Kinematics publishing to robot_description.launch

### Add RViz to world.launch

## Manually drive Robot
## Launch ROS

## Setup RViz
RViz Setup
Setup RViz to visualize the sensor readings. On the left side of RViz, under Displays:

1. Select odom for fixed frame
2. Click the Add button and
3. add RobotModel and your robot model should load up in RViz.
4. add Camera and select the Image topic that was defined in the camera Gazebo plugin
5. add LaserScan and select the topic that was defined in the Hokuyo Gazebo plugin

## Drive!
###  Send command to diff. controller topic
rostopic pub /cmd_vel geometry_msgs/Twist  "linear:
  x: 0.1
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.1" 

## Copy World

# Code drive_bot

## Create the ball_chaser Package
$ cd /home/workspace/catkin_ws/src/
$ catkin_create_pkg ball_chaser roscpp std_msgs message_generation

## Create DriveToTarget Service
1. Create .srv file
2. rossrv show DriveToTarget


## Create cpp and modify CMake
1. drive_bot.cpp

## Test
1. Window 1:
roslaunch my_robot world.launch

2. Window 2:
rosrun ball_chaser drive_bot

3. Window 3:
$ rosservice call /ball_chaser/command_robot "linear_x: 0.5
angular_z: 0.0"  # This request should drive your robot forward

$ rosservice call /ball_chaser/command_robot "linear_x: 0.0
angular_z: 0.5"  # This request should drive your robot left

$ rosservice call /ball_chaser/command_robot "linear_x: 0.0
angular_z: -0.5"  # This request should drive your robot right

$ rosservice call /ball_chaser/command_robot "linear_x: 0.0
angular_z: 0.0"  # This request should bring your robot to a complete stop

## Add to ball_chaser.launch

# Code process_image
## Create cpp and modify CMake
1. process_image.cpp

## Modify ball_chaser.launch

# Test
## Start robot inside world
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot world.launch

## Run drive_bot and process_image
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch ball_chaser ball_chaser.launch

## Visualize
$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ rosrun rqt_image_view rqt_image_view





# Helpers
rosnode list
rostopic list
rostopic info /topic
rosmsg info geometry_msgs/Twist

## Echo Topic Messages
rostopic echo /turtle1/cmd_vel

