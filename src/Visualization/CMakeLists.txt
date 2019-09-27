cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release)

find_package(VTK REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include/Visualization) 

file(GLOB SOURCES "*.cpp")

add_library(visualization STATIC ${SOURCES})
target_link_libraries(visualization ${VTK_LIBRARIES})
 
install( TARGETS visualization 
		 ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/install/libs
		 FRAMEWORK DESTINATION ${CMAKE_SOURCE_DIR}/install/libs
		 LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/install/libs)

install( TARGETS visualization DESTINATION ${CMAKE_SOURCE_DIR}/install/libs)