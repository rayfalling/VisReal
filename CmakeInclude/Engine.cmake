cmake_minimum_required(VERSION 3.14)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Shared Libraries
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
mark_as_advanced(BUILD_SHARED_LIBS)

set(LIB_TYPE STATIC)
if (BUILD_SHARED_LIBS)
    # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
    set(LIB_TYPE SHARED)
endif (BUILD_SHARED_LIBS)

include(GenerateExportHeader)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/DetectPlatform.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/glad.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/glfw.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/spdlog.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/xxhash.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/FindD3D12.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/Engine)
add_subdirectory(${CMAKE_SOURCE_DIR}/Test)