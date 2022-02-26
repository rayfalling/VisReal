cmake_minimum_required(VERSION 3.17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/Library/glfw)

set(GLFW_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/Library/glfw/include)

set_target_properties(glfw PROPERTIES FOLDER VisReal/Engine/Library)
