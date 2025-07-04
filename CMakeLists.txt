cmake_minimum_required(VERSION 2.8.12)
project(mavros_controllers)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  dynamic_reconfigure
  tf
  mavros
  mavros_extras
  mavros_msgs
  mavlink
  message_generation
  std_msgs
  geometry_msgs
  sensor_msgs
)

add_message_files(
  FILES
  FlatTarget.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
)

generate_dynamic_reconfigure_options(
  config/MavrosControllers.cfg
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES mavros_controllers
  CATKIN_DEPENDS roscpp rospy std_msgs mavros_msgs geometry_msgs sensor_msgs tf message_runtime
)

#############
# LIBRARIES #
#############
include_directories(
  include
  ${Boost_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/controller_manager.cpp 
  src/nonlinear_attitude_control.cpp
  src/nonlinear_geometric_control.cpp
  src/jerk_tracking_control.cpp
)
add_dependencies(mavros_controllers ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

############
# BINARIES #
############
add_executable(mavros_controllers_node
  src/main.cpp
)
add_dependencies(mavros_controllers_node mavros_controllers ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(mavros_controllers_node ${PROJECT_NAME} ${catkin_LIBRARIES})
##########
# EXPORT #
##########
# Install shell scripts
install(PROGRAMS
  scripts/takeoff.sh
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/scripts
)
#############
## Testing ##
#############

# Temporarily disabled tests
#if(CATKIN_ENABLE_TESTING)
#    # Add gtest based cpp test target and link libraries
#    catkin_add_gtest(${PROJECT_NAME}-test test/main.cpp
#                                          test/test_example.cpp
#                                          test/geometric_controller-test.cpp)
#
#    if(TARGET ${PROJECT_NAME}-test)
#        target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME}
#                                                 ${catkin_LIBRARIES}
#                                                 ${YAML_CPP_LIBRARIES})
#    endif()
#
#endif()
