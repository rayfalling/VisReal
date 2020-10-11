cmake_minimum_required(VERSION 3.14)

include(CmakeInclude/DetectPlatform.cmake)
include(CmakeInclude/glad.cmake)
include(CmakeInclude/glfw.cmake)
include(CmakeInclude/FindD3D12.cmake)

#include(CmakeInclude/DirectXShaderCompiler.cmake)

add_subdirectory(${PROJECT_SOURCE_DIR}/Engine)

target_link_libraries(${PROJECT_NAME} Engine)