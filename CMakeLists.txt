cmake_minimum_required(VERSION 3.21)
project(image_processing)

set(CMAKE_CXX_STANDARD 11)

add_executable(image_processing main.cpp ImagePPM.cpp ImagePPM.h)
