cmake_minimum_required(VERSION 3.21)
project(image_processing)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(test)

set(SOURCE_FILES Pixel.cpp Pixel.h Image.cpp Image.h ImageProcessing.cpp ImageProcessing.h ImagePPM.cpp ImagePPM.h ImagePGM.cpp ImagePGM.h ImageFactory.cpp ImageFactory.h)
add_executable(image_processing main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(image_processing core)
