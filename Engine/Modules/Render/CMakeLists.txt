cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine.Render" C CXX)

# include all header files
set("ENGINE_RENDER_INCLUDE_DIR" ${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${ENGINE_RENDER_INCLUDE_DIR})
file(GLOB_RECURSE ENGINE_RENDER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/Include/*)
aux_source_directory(Source ENGINE_RENDER_SOURCE)
aux_source_directory(Source/OpenGL ENGINE_RENDER_SOURCE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_RENDER_INCLUDE} ${ENGINE_RENDER_SOURCE})

add_library(${PROJECT_NAME} ${LIB_TYPE} ${ENGINE_RENDER_INCLUDE} ${ENGINE_RENDER_SOURCE})
if (BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_RENDER_SHARED)
    GENERATE_EXPORT_HEADER(
            ${PROJECT_NAME}
            BASE_NAME ENGINE_RENDER
            EXPORT_MACRO_NAME ENGINE_RENDER_EXPORTS
            EXPORT_FILE_NAME ${ENGINE_RENDER_INCLUDE_DIR}/EngineRenderExport.generate.h
            STATIC_DEFINE ENGINE_RENDER_EXPORTS_BUILT_AS_STATIC
    )
endif(BUILD_SHARED_LIBS)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Engine)

# expose include headers
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_RENDER_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC Engine.Core PRIVATE glad PRIVATE glfw)
