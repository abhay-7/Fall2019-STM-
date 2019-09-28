cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release)

find_package(VTK REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(${CMAKE_SOURCE_DIR}/include/Visualization ${VTK_INCLUDE_DIRS}) 

file(GLOB SOURCES "*.cpp")

add_library(visualization STATIC ${SOURCES})

target_link_libraries(visualization ${VTK_LIBRARIES})