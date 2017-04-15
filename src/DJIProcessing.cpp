#include "ros/ros.h"
#include "sensor_msgs/Joy.h"

ros::Publisher joy_cmd_pub;
ros::Subscriber joy_cmd_sub;


void joy_callback(const sensor_msgs::Joy::ConstPtr& joy_msg){
    
	//ROS_INFO("Axis %d is now at position %l", 0, joy_msg->buttons[0]);
//the joy_msg contains 6 readings

	ROS_INFO("%d",  joy_msg->buttons[0]);
  ROS_INFO("%d",  joy_msg->buttons[1]);


    sensor_msgs::Joy joy_cmd;
    //left lr   right ud  right lr
    joy_cmd.buttons.push_back(joy_msg->buttons[0]+2);
    joy_cmd.buttons.push_back(1024);
    joy_cmd.buttons.push_back(1024);	
 	   	
    joy_cmd_pub.publish(joy_cmd);

}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "DJIProcessing");
  ros::NodeHandle n;
  joy_cmd_pub = n.advertise<sensor_msgs::Joy>("joy_cmd", 1000);
  joy_cmd_sub = n.subscribe("joy_msg", 1000, joy_callback);

  ros::spin();


  return 0;
}
