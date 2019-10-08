cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release)

find_package(VTK REQUIRED)

include(${VTK_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/include/Visualization /usr/local/include/vtk-8.90)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_executable(test_visualizer test_visualizer.cpp)

link_directories(${CMAKE_SOURCE_DIR}/install/libs
				 ${CMAKE_SOURCE_DIR}/build/src/Visualization)

target_link_libraries( test_visualizer 
						${CMAKE_SOURCE_DIR}/build/src/Visualization/libvisualization.a
						${VTK_LIBRARIES})
 
#install(TARGETS test_visualizer DESTINATION ${CMAKE_SOURCE_DIR}/install/test/)