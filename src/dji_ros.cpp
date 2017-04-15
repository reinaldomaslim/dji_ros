#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "keyboard/Key.h"

ros::Publisher joy_cmd_pub;
ros::Subscriber joy_cmd_sub;


#ifdef KEYBOARD_CONTROL

ros::Subscriber keyboard_up_sub;
ros::Subscriber keyboard_down_sub;

#define KEYBOARD_A 97
#define KEYBOARD_W 119
#define KEYBOARD_S 115
#define KEYBOARD_D 100
#define KEYBOARD_LEFT 276
#define KEYBOARD_RIGHT 275
bool keyboard_a_flag = false;
bool keyboard_w_flag = false;
bool keyboard_s_flag = false;
bool keyboard_d_flag = false;
bool keyboard_left_flag = false;
bool keyboard_right_flag = false;
void keyboard_down_callback(const keyboard::Key::ConstPtr& keyboard_down_msg){
  switch(keyboard_down_msg->code  ){
    case KEYBOARD_A: keyboard_a_flag = true;break;
    case KEYBOARD_W: keyboard_w_flag = true;break;
    case KEYBOARD_S: keyboard_s_flag = true;break;
    case KEYBOARD_D: keyboard_d_flag = true;break;
    case KEYBOARD_LEFT: keyboard_left_flag = true;break;
    case KEYBOARD_RIGHT: keyboard_right_flag = true;break;
    default:break;
  }
}
void keyboard_up_callback(const keyboard::Key::ConstPtr& keyboard_up_msg){
  switch(keyboard_up_msg->code){
    case KEYBOARD_A: keyboard_a_flag = false;break;
    case KEYBOARD_W: keyboard_w_flag = false;break;
    case KEYBOARD_S: keyboard_s_flag = false;break;
    case KEYBOARD_D: keyboard_d_flag = false;break;
    case KEYBOARD_LEFT: keyboard_left_flag = false;break;
    case KEYBOARD_RIGHT: keyboard_right_flag = false;break;
    default:break;
  }
}

#endif

#define SPEED_MID 1024
#define SPEED_HIGH 1300
#define SPEED_LOW 700

void joy_callback(const sensor_msgs::Joy::ConstPtr& joy_msg){
    
	//ROS_INFO("Axis %d is now at position %l", 0, joy_msg->buttons[0]);
//the joy_msg contains 6 readings

	ROS_INFO("%d",  joy_msg->buttons[0]);
  ROS_INFO("%d",  joy_msg->buttons[1]);
  ROS_INFO("%d",  joy_msg->buttons[2]);
  ROS_INFO("%d",  joy_msg->buttons[3]);




  sensor_msgs::Joy joy_cmd;

    //left lr   right ud  right lr
#ifdef KEYBOARD_CONTROL
  int roll,pitch,yaw;
  if(keyboard_a_flag && keyboard_d_flag){
    roll = SPEED_MID;
  }else if(keyboard_a_flag){
    roll = SPEED_LOW;
  }else if(keyboard_d_flag){
    roll = SPEED_HIGH;
  }else{
    roll = SPEED_MID;
  }

  if(keyboard_w_flag && keyboard_s_flag){
    pitch = SPEED_MID;
  }else if(keyboard_s_flag){
    pitch = SPEED_LOW;
  }else if(keyboard_w_flag){
    pitch = SPEED_HIGH;
  }else{
    pitch = SPEED_MID;
  }

  if(keyboard_left_flag && keyboard_right_flag){
    yaw = SPEED_MID;
  }else if(keyboard_left_flag){
    yaw = SPEED_LOW;
  }else if(keyboard_right_flag){
    yaw = SPEED_HIGH;
  }else{
    yaw = SPEED_MID;
  }

  joy_cmd.buttons.push_back(yaw);
  joy_cmd.buttons.push_back(pitch);
  joy_cmd.buttons.push_back(roll);  
#else
  joy_cmd.buttons.push_back(SPEED_MID);
  joy_cmd.buttons.push_back(SPEED_MID);
  joy_cmd.buttons.push_back(SPEED_MID); 
#endif 	   	
  joy_cmd_pub.publish(joy_cmd);

}



int main(int argc, char **argv)
{

  ros::init(argc, argv, "dji_ros");
  ros::NodeHandle n;
  joy_cmd_pub = n.advertise<sensor_msgs::Joy>("joy_cmd", 1000);
  joy_cmd_sub = n.subscribe("joy_msg", 1000, joy_callback);

#ifdef KEYBOARD_CONTROL
  keyboard_up_sub = n.subscribe("/keyboard_listen/keyup", 1000, keyboard_up_callback);
  keyboard_down_sub = n.subscribe("/keyboard_listen/keydown", 1000, keyboard_down_callback);
#endif

  
  ros::spin();

  return 0;
}
