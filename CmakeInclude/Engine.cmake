cmake_minimum_required(VERSION 3.14)

include(${CMAKE_SOURCE_DIR}/CmakeInclude/DetectPlatform.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/glad.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/glfw.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/FindD3D12.cmake)

#include(CmakeInclude/DirectXShaderCompiler.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/Engine)

target_link_libraries(${PROJECT_NAME} Engine)