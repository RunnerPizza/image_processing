cmake_minimum_required(VERSION 3.21)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp ImageFixture.cpp)
add_executable(runImageProcessingTests ${TEST_SOURCE_FILES})
target_link_libraries(runImageProcessingTests gtest gtest_main core)