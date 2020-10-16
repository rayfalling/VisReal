cmake_minimum_required(VERSION 3.14)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)

SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
    # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
    SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

include(GenerateExportHeader)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/DetectPlatform.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/glad.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/glfw.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/spdlog.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeInclude/FindD3D12.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/Engine)

target_link_libraries(${PROJECT_NAME} Engine)