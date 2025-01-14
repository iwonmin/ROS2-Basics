cmake_minimum_required(VERSION 3.5)
project(ros2_cpp_tutorial)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(std_srvs REQUIRED)

add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME})

add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)
install(TARGETS
  listener
  DESTINATION lib/${PROJECT_NAME})

add_executable(double_talker src/p1_publisher.cpp)
ament_target_dependencies(double_talker rclcpp std_msgs)
install(TARGETS
  double_talker
  DESTINATION lib/${PROJECT_NAME})

add_executable(double_listener src/p1_subscriber.cpp)
ament_target_dependencies(double_listener rclcpp std_msgs)
install(TARGETS
  double_listener
  DESTINATION lib/${PROJECT_NAME})

add_executable(slow_agent src/p2_slow_agent.cpp)
ament_target_dependencies(slow_agent rclcpp std_msgs)
install(TARGETS
  slow_agent
  DESTINATION lib/${PROJECT_NAME})
  
add_executable(fast_agent src/p2_fast_agent.cpp)
ament_target_dependencies(fast_agent rclcpp std_msgs)
install(TARGETS
  fast_agent
  DESTINATION lib/${PROJECT_NAME})
add_executable(server src/add_two_ints_server.cpp)
ament_target_dependencies(server rclcpp example_interfaces)
install(TARGETS
  server
  DESTINATION lib/${PROJECT_NAME})
  
add_executable(client src/add_two_ints_client.cpp)
ament_target_dependencies(client rclcpp example_interfaces)
install(TARGETS
  client
    DESTINATION lib/${PROJECT_NAME})
    
add_executable(led_server src/toggle_led_server.cpp)
ament_target_dependencies(led_server rclcpp std_srvs)
install(TARGETS
  led_server
    DESTINATION lib/${PROJECT_NAME})

add_executable(led_client src/toggle_led_client.cpp)
ament_target_dependencies(led_client rclcpp std_srvs)
install(TARGETS
  led_client
    DESTINATION lib/${PROJECT_NAME})
ament_package()