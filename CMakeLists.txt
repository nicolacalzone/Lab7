cmake_minimum_required(VERSION 3.1)
project(lab7)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(task1 task1.cpp matcher_methods descriptor_methods utils panoramic_utils2 Stitch)
target_link_libraries(task1 ${OpenCV_LIBS})