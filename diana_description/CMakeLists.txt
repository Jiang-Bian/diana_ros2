cmake_minimum_required(VERSION 3.5)
project(diana_description)
find_package(ament_cmake REQUIRED)


# if(BUILD_TESTING)
#   find_package(ament_lint_auto REQUIRED)
#   ament_lint_auto_find_test_dependencies()

#   find_package(ament_cmake_pytest REQUIRED)
#   ament_add_pytest_test(${PROJECT_NAME}_urdf_tests test/urdf_tests.py)

# endif()

# Install launch files.
install(
  DIRECTORY
    common
    config
    end_effectors
    launch
    rviz
    meshes
    robots
  DESTINATION
    share/${PROJECT_NAME}
)

ament_package()