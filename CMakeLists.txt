cmake_minimum_required(VERSION 2.8.3)
project(dji_ros)

## Add support for C++11, supported in ROS Kinetic and newer
# add_definitions(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  message_generation
)
find_package(SDL REQUIRED)
set(LIBS ${SDL_LIBRARY})

add_message_files(
  FILES
  Key.msg
)
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES dji_infantry
   CATKIN_DEPENDS roscpp sensor_msgs std_msgs message_runtime
   DEPENDS ${LIBS}
)

include_directories(
  ${catkin_INCLUDE_DIRS} ${SDL_INCLUDE_DIR}
)

add_executable(dji_ros src/dji_ros.cpp)
target_link_libraries(dji_ros ${catkin_LIBRARIES})
add_dependencies(dji_ros dji_ros_generate_messages_cpp)

add_executable(dji_ros_withkeyboard src/dji_ros_withkeyboard.cpp)
target_link_libraries(dji_ros_withkeyboard ${catkin_LIBRARIES})
add_dependencies(dji_ros_withkeyboard dji_ros_withkeyboard_generate_messages_cpp)

add_executable(keyboard_listen src/keyboard_listen.cpp src/keyboard.cpp)
target_link_libraries(keyboard_listen
  ${LIBS}
  ${catkin_LIBRARIES}
)
add_dependencies(keyboard_listen keyboard_listen_gencpp)

install(TARGETS keyboard_listen
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)