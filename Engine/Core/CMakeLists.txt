cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine.Core" C CXX)

# Set CXX flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS   "-std=c++11")             # c++17
set(CMAKE_CXX_FLAGS   "-Wall")                  # 开启所有警告

set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g" )             # 调试包不优化
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )   # release包优化

add_subdirectory(Object)
add_subdirectory(Render)
add_subdirectory(Type)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE "Engine.Core.Object" "Engine.Core.Render" "Engine.Core.Type")