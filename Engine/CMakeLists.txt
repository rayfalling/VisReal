cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine" C CXX)

# Make codecvt work for c++17
add_compile_definitions(_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)

# Set CXX flags
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g" )             # 调试包不优化
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )   # release包优化

add_subdirectory(Core)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE "Engine.Core")