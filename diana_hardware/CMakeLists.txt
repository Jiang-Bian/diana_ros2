cmake_minimum_required(VERSION 3.16)

project(diana_hardware LANGUAGES CXX)

##############################################################################
# Build Options
##############################################################################

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

##############################################################################
# Dependencies
##############################################################################

find_package(ament_cmake REQUIRED)

find_package(pluginlib REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)

find_package(hardware_interface REQUIRED)

##############################################################################
# Library
##############################################################################

add_library(${PROJECT_NAME} SHARED
    src/diana_system.cpp
    src/fake_hardware_driver.cpp
    src/fci_hardware_driver.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    DIANA_HARDWARE_BUILDING_DLL
)

ament_target_dependencies(${PROJECT_NAME}

    hardware_interface

    pluginlib

    rclcpp

    rclcpp_lifecycle
)

##############################################################################
# Plugin Export
##############################################################################

pluginlib_export_plugin_description_file(
    hardware_interface
    plugin.xml
)

##############################################################################
# Install
##############################################################################

install(
    TARGETS ${PROJECT_NAME}
    EXPORT export_${PROJECT_NAME}

    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    FILES plugin.xml
    DESTINATION share/${PROJECT_NAME}
)

##############################################################################
# Export
##############################################################################

ament_export_targets(
    export_${PROJECT_NAME}
)

ament_export_dependencies(
    hardware_interface
    pluginlibcmake_minimum_required(VERSION 3.16)

project(diana_hardware)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)

find_package(pluginlib REQUIRED)

find_package(hardware_interface REQUIRED)

add_library(${PROJECT_NAME} SHARED
    src/diana_system.cpp
    src/fake_hardware_driver.cpp
    src/fci_hardware_driver.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include
)

ament_target_dependencies(${PROJECT_NAME}
    rclcpp
    rclcpp_lifecycle
    pluginlibcmake_minimum_required(VERSION 3.16)

project(diana_hardware)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)

find_package(pluginlib REQUIRED)

find_package(hardware_interface REQUIRED)

add_library(${PROJECT_NAME} SHARED
    src/diana_system.cpp
    src/fake_hardware_driver.cpp
    src/fci_hardware_driver.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include
)

ament_target_dependencies(${PROJECT_NAME}
    rclcpp
    rclcpp_lifecycle
    pluginlibcmake_minimum_required(VERSION 3.16)

project(diana_hardware)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)

find_package(pluginlib REQUIRED)

find_package(hardware_interface REQUIRED)

add_library(${PROJECT_NAME} SHARED
    src/diana_system.cpp
    src/fake_hardware_driver.cpp
    src/fci_hardware_driver.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include
)

ament_target_dependencies(${PROJECT_NAME}
    rclcpp
    rclcpp_lifecycle
    pluginlib
    hardware_interface
)

pluginlib_export_plugin_description_file(
    hardware_interface
    plugin.xml
)

install(
    TARGETS
    ${PROJECT_NAME}
    LIBRARY DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    FILES plugin.xml
    DESTINATION share/${PROJECT_NAME}
)

ament_package()

    hardware_interface
)

pluginlib_export_plugin_description_file(
    hardware_interface
    plugin.xml
)

install(
    TARGETS
    ${PROJECT_NAME}
    LIBRARY DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    FILES plugin.xml
    DESTINATION share/${PROJECT_NAME}
)

ament_package()

    hardware_interface
)

pluginlib_export_plugin_description_file(
    hardware_interface
    plugin.xml
)

install(
    TARGETS
    ${PROJECT_NAME}
    LIBRARY DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    FILES plugin.xml
    DESTINATION share/${PROJECT_NAME}
)

ament_package()

    rclcpp
    rclcpp_lifecycle
)

ament_export_include_directories(
    include
)

##############################################################################
# Testing
##############################################################################

if(BUILD_TESTING)

    find_package(ament_lint_auto REQUIRED)

    ament_lint_auto_find_test_dependencies()

endif()

##############################################################################
# Package
##############################################################################

ament_package()
