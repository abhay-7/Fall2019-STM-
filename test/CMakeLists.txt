cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release)

find_package(VTK REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include/Visualization) 

add_executable(test_visualizer test_visualizer.cpp)

link_directories(${CMAKE_SOURCE_DIR}/install/libs
				 ${CMAKE_SOURCE_DIR}/build/src/)
target_link_libraries( test_visualizer libvisualization.a)
 
install(TARGETS test_visualizer DESTINATION ${CMAKE_SOURCE_DIR}/install/test/)