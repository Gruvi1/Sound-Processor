cmake_minimum_required(VERSION 3.05)

project(sound_processor)

include_directories(./include ./src)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../bin)

file (GLOB SOURCES ./main.cpp "./src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})