cmake_minimum_required(VERSION 3.17)
project(VisReal C CXX)

set(CMAKE_CXX_STANDARD 17)

# Set Cmake build output
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binary/Library)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binary)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binary)

if(POLICY CMP0077)
    set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
endif()

# hacker for glfw uninstall target
add_custom_target(uninstall)
set_target_properties(uninstall PROPERTIES FOLDER CMakeTargets)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

file(GLOB_RECURSE CMAKE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeInclude/*.cmake)
source_group(cmake FILES ${CMAKE_FILES})

# include libs cmake
include(CmakeInclude/Engine.cmake)