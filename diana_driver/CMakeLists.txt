cmake_minimum_required(VERSION 3.16)

project(diana_driver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)

add_library(${PROJECT_NAME} SHARED
  src/driver.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
  include
)

install(

  TARGETS

  ${PROJECT_NAME}

  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY include/
  DESTINATION include
)

ament_package()
