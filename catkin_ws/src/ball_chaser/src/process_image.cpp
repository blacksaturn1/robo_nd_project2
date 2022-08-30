#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x=lin_x;
    srv.request.angular_z=ang_z;
    if (!client.call(srv))
        ROS_ERROR("Failed to call service DriveToTarget");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    int no_white = -1;
    int location_x=no_white;
    std::string msg_feedback = "";
    int lmr=img.step/3;
    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // RGB is 3 bytes
    for(int x=0;x<(img.height*img.step)-3;x+=3){
	if(img.data[x]==white_pixel && img.data[x+1]==white_pixel && img.data[x+2]==white_pixel){
   	   location_x=x;
           // Then, identify if this pixel falls in the left, mid, or right side of the image
   	   int location=location_x - ((location_x/img.step)*img.step)+1;
           msg_feedback="Img_Loc: "+std::to_string(location_x)+", Step: "+std::to_string(img.step)+", LMR: "+std::to_string(lmr)+", Ball location: "+std::to_string(location);
           ROS_INFO_STREAM(msg_feedback);
           // Depending on the white ball position, call the drive_bot function and pass velocities to it
           if(location<=lmr){
              // move left
		drive_robot(0.125,0.35);
           }
           else if(location>2*lmr){
              // move right
       		drive_robot(0.125,-0.35);
           }
           else{
              // move straight
		ROS_INFO_STREAM("Sending STR Drive cmd");
       		drive_robot(0.15,0.0);
            }

           return;
	}
    }
    // Request a stop when there's no white ball seen by the camera
    if(location_x==no_white){
       // ROS_INFO_STREAM("Sending STOP Drive cmd");
       drive_robot(0.0,0.45);
    }
    
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
