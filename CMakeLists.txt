cmake_minimum_required(VERSION 3.17)
project(VisReal C CXX)

set(CMAKE_CXX_STANDARD 17)

# add executable before include library for test use
add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")

# include libs cmake
include(CmakeInclude/Engine.cmake)