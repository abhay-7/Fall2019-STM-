cmake_minimum_required(VERSION 3.5)

project(3DUltrasound LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(VTK REQUIRED)

include_directories(${VTK_INCLUDE_DIRS})

add_executable(3DUltrasound
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  sonogram_structure.h
  visualizer.cpp
  visualizer.hpp
)


target_link_libraries(3DUltrasound PRIVATE Qt5::Widgets)

