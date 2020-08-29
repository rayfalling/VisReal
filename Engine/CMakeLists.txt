cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine" C CXX)

# Set CXX flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS   "-std=c++11")             # c++17
set(CMAKE_CXX_FLAGS   "-Wall")                  # 开启所有警告

set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g" )             # 调试包不优化
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )   # release包优化

add_subdirectory(Core)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE "Engine.Core")