cmake_minimum_required(VERSION 3.17)
project(VisReal C CXX)

set(CMAKE_CXX_STANDARD 17)

# Set Cmake build output
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binary/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binary)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binary)

# hacker for glfw uninstall target
add_custom_target(uninstall)
set_target_properties(uninstall PROPERTIES FOLDER CMakePredefinedTargets)

# include libs cmake
include(CmakeInclude/Engine.cmake)