#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
//TODO: Include the ball_chaser "DriveToTarget" header file
#include "ball_chaser/DriveToTarget.h"

class Drive_Bot
{
public:
  Drive_Bot()
  {
     // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
    // See: https://answers.ros.org/question/214597/service-with-class-method/
    // And http://wiki.ros.org/roscpp_tutorials/Tutorials/UsingClassMethodsAsCallbacks#Service_Servers
    service_ = n_.advertiseService("/ball_chaser/command_robot", &Drive_Bot::handle_drive_request,this);
    
    }

  bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& resp)
  {
    ROS_INFO("DriveToTarget received - linear_x:%1.2f, j2:%1.2f", (float)req.linear_x, 
      (float)req.angular_z);

    // Create a motor_command object of type geometry_msgs::Twist
    geometry_msgs::Twist motor_command;
    // Set wheel velocities
    // X
    motor_command.linear.x = req.linear_x;
    // Yaw
    motor_command.angular.z = req.angular_z;
    // Publish angles to drive the robot
    motor_command_publisher_.publish(motor_command);
    resp.msg_feedback = "Motor command set - x: " + std::to_string(req.linear_x) + " , z: " + std::to_string(req.angular_z);;
    ROS_INFO_STREAM(resp.msg_feedback);
    return true;
  }

private:
  ros::NodeHandle n_; 
  ros::Publisher motor_command_publisher_;
  ros::Subscriber sub_;
  ros::ServiceServer service_;

};//End of class Drive_Bot

int main(int argc, char **argv)
{
    //Initiate ROS node
    ros::init(argc, argv, "drive_bot");

    //Create an object of class Drive_Bot that will take care of everything
    Drive_Bot DBObject;

    ROS_INFO("Ready to send motor commands");

    // Handle ROS communication events
    ros::spin();

  return 0;
}