cmake_minimum_required(VERSION 2.8.3)
project(fuse_constraints)

set(build_depends
  fuse_core
  fuse_graphs
  fuse_variables
  geometry_msgs
  pluginlib
  roscpp
)

find_package(catkin REQUIRED COMPONENTS
  ${build_depends}
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
find_package(Ceres REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(SuiteSparse REQUIRED COMPONENTS CCOLAMD)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    ${PROJECT_NAME}
  CATKIN_DEPENDS
    ${build_depends}
  DEPENDS
    CERES
    EIGEN3
    SUITESPARSE
)

###########
## Build ##
###########

add_compile_options(-std=c++14 -Wall -Werror)

# fuse_constraints library
add_library(${PROJECT_NAME}
  src/absolute_constraint.cpp
  src/absolute_orientation_3d_stamped_constraint.cpp
  src/absolute_orientation_3d_stamped_euler_constraint.cpp
  src/absolute_pose_2d_stamped_constraint.cpp
  src/absolute_pose_3d_stamped_constraint.cpp
  src/marginal_constraint.cpp
  src/marginal_cost_function.cpp
  src/marginalize_variables.cpp
  src/normal_delta.cpp
  src/normal_delta_orientation_2d.cpp
  src/normal_prior_orientation_2d.cpp
  src/relative_constraint.cpp
  src/relative_orientation_3d_stamped_constraint.cpp
  src/relative_pose_2d_stamped_constraint.cpp
  src/relative_pose_3d_stamped_constraint.cpp
  src/uuid_ordering.cpp
  src/variable_constraints.cpp
)
add_dependencies(${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)
target_include_directories(${PROJECT_NAME}
  PUBLIC
    include
    ${catkin_INCLUDE_DIRS}
    ${CERES_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
    ${SUITESPARSE_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${CERES_LIBRARIES}
  ${EIGEN3_LIBRARIES}
  ${SUITESPARSE_LIBRARIES}
)

#############
## Install ##
#############

install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(
  FILES fuse_plugins.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

#############
## Testing ##
#############

if(CATKIN_ENABLE_TESTING)
  find_package(roslint REQUIRED)
  find_package(rostest REQUIRED)

  # Lint tests
  set(ROSLINT_CPP_OPTS "--filter=-build/c++11,-runtime/references")
  roslint_cpp()
  roslint_add_test()

  # Absolute Constraint Tests
  catkin_add_gtest(test_absolute_constraint
    test/test_absolute_constraint.cpp
  )
  add_dependencies(test_absolute_constraint
    ${catkin_EXPORTED_TARGETS}
  )
  target_include_directories(test_absolute_constraint
    PRIVATE
      include
      ${catkin_INCLUDE_DIRS}
      ${CERES_INCLUDE_DIRS}
  )
  target_link_libraries(test_absolute_constraint
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${CERES_LIBRARIES}
  )

  # Absolute Orientation 3D Stamped Constraint Tests
  catkin_add_gtest(test_absolute_orientation_3d_stamped_constraint
    test/test_absolute_orientation_3d_stamped_constraint.cpp
  )
  add_dependencies(test_absolute_orientation_3d_stamped_constraint
    ${catkin_EXPORTED_TARGETS}
  )
  target_include_directories(test_absolute_orientation_3d_stamped_constraint
    PRIVATE
      include
      ${catkin_INCLUDE_DIRS}
      ${CERES_INCLUDE_DIRS}
      ${EIGEN3_INCLUDE_DIRS}
  )
  target_link_libraries(test_absolute_orientation_3d_stamped_constraint
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${CERES_LIBRARIES}
    ${EIGEN3_LIBRARIES}
  )

  # Absolute Orientation 3D Stamped Euler Constraint Tests
    catkin_add_gtest(test_absolute_orientation_3d_stamped_euler_constraint
    test/test_absolute_orientation_3d_stamped_euler_constraint.cpp
  )
  add_dependencies(test_absolute_orientation_3d_stamped_euler_constraint
    ${catkin_EXPORTED_TARGETS}
  )
  target_include_directories(test_absolute_orientation_3d_stamped_euler_constraint
    PRIVATE
      include
      ${catkin_INCLUDE_DIRS}
      ${CERES_INCLUDE_DIRS}
      ${EIGEN3_INCLUDE_DIRS}
  )
  target_link_libraries(test_absolute_orientation_3d_stamped_euler_constraint
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${CERES_LIBRARIES}
    ${EIGEN3_LIBRARIES}
  )

  # Absolute Pose 2D Stamped Constraint Tests
  catkin_add_gtest(test_absolute_pose_2d_stamped_constraint
    test/test_absolute_pose_2d_stamped_constraint.cpp
  )
  add_dependencies(test_absolute_pose_2d_stamped_constraint
    ${catkin_EXPORTED_TARGETS}
  )
  target_include_directories(test_absolute_pose_2d_stamped_constraint
    PRIVATE
      include
      ${catkin_INCLUDE_DIRS}
      ${CERES_INCLUDE_DIRS}
  )
  target_link_libraries(test_absolute_pose_2d_stamped_constraint
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${CERES_LIBRARIES}
  )

  # Absolute Pose 3D Stamped Constraint Tests
  catkin_add_gtest(test_absolute_pose_3d_stamped_constraint
    test/test_absolute_pose_3d_stamped_constraint.cpp
  )
  add_dependencies(test_absolute_pose_3d_stamped_constraint
    ${catkin_EXPORTED_TARGETS}
  )
  target_include_directories(test_absolute_pose_3d_stamped_constraint
    PRIVATE
      include
      ${catkin_INCLUDE_DIRS}
      ${CERES_INCLUDE_DIRS}
  )
  target_link_libraries(test_absolute_pose_3d_stamped_constraint
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${CERES_LIBRARIES}
  )

  # Marginal Constraint Tests
  catkin_add_gtest(test_marginal_constraint
    test/test_marginal_constraint.cpp
  )
  add_dependencies(test_marginal_constraint
    ${catkin_EXPORTED_TARGETS}
  )
  target_include_directories(test_marginal_constraint
    PRIVATE
      include
      ${catkin_INCLUDE_DIRS}
  )
  target_link_libraries(test_marginal_constraint
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
  )

  # Marginalize Variables Tests
  catkin_add_gtest(test_marginalize_variables
    test/test_marginalize_variables.cpp
  )
  add_dependencies(test_marginalize_variables
    ${catkin_EXPORTED_TARGETS}
  )
  target_include_directories(test_marginalize_variables
    PRIVATE
      include
      ${catkin_INCLUDE_DIRS}
      ${CERES_INCLUDE_DIRS}
  )
  target_link_libraries(test_marginalize_variables
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
  )

  # Relative Constraint Tests
  catkin_add_gtest(test_relative_constraint
    test/test_relative_constraint.cpp
  )
  add_dependencies(test_relative_constraint
    ${catkin_EXPORTED_TARGETS}
  )
  target_include_directories(test_relative_constraint
    PRIVATE
      include
      ${catkin_INCLUDE_DIRS}
      ${CERES_INCLUDE_DIRS}
  )
  target_link_libraries(test_relative_constraint
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${CERES_LIBRARIES}
  )

  # Relative Pose 2D Stamped Constraint Tests
  catkin_add_gtest(test_relative_pose_2d_stamped_constraint
    test/test_relative_pose_2d_stamped_constraint.cpp
  )
  add_dependencies(test_relative_pose_2d_stamped_constraint
    ${catkin_EXPORTED_TARGETS}
  )
  target_include_directories(test_relative_pose_2d_stamped_constraint
    PRIVATE
      include
      ${catkin_INCLUDE_DIRS}
      ${CERES_INCLUDE_DIRS}
  )
  target_link_libraries(test_relative_pose_2d_stamped_constraint
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${CERES_LIBRARIES}
  )

  # Relative Pose 3D Stamped Constraint Tests
  catkin_add_gtest(test_relative_pose_3d_stamped_constraint
    test/test_relative_pose_3d_stamped_constraint.cpp
  )
  add_dependencies(test_relative_pose_3d_stamped_constraint
    ${catkin_EXPORTED_TARGETS}
  )
  target_include_directories(test_relative_pose_3d_stamped_constraint
    PRIVATE
      include
      ${catkin_INCLUDE_DIRS}
      ${CERES_INCLUDE_DIRS}
  )
  target_link_libraries(test_relative_pose_3d_stamped_constraint
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${CERES_LIBRARIES}
  )

  # UuidOrdering Tests
  catkin_add_gtest(test_uuid_ordering
    test/test_uuid_ordering.cpp
  )
  target_include_directories(test_uuid_ordering
    PRIVATE
      include
      ${catkin_INCLUDE_DIRS}
  )
  target_link_libraries(test_uuid_ordering
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
  )

  # VariableConstraints Tests
  catkin_add_gtest(test_variable_constraints
    test/test_variable_constraints.cpp
  )
  target_include_directories(test_variable_constraints
    PRIVATE
      include
  )
  target_link_libraries(test_variable_constraints
    ${PROJECT_NAME}
  )
endif()
