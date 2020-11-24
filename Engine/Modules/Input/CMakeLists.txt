cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine.Input" C CXX)

# Set CXX flags
set(CMAKE_CXX_STANDARD 17)

# include all header files
set("ENGINE_INPUT_INCLUDE_DIR" ${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${ENGINE_INPUT_INCLUDE_DIR})
file(GLOB_RECURSE ENGINE_INPUT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/Include/*)
aux_source_directory(Source ENGINE_INPUT_SOURCE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_INPUT_INCLUDE} ${ENGINE_INPUT_SOURCE})

add_library(${PROJECT_NAME} ${LIB_TYPE} ${ENGINE_INPUT_INCLUDE} ${ENGINE_INPUT_SOURCE})
if (BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_INPUT_SHARED)
    GENERATE_EXPORT_HEADER(
            ${PROJECT_NAME}
            BASE_NAME ENGINE_INPUT
            EXPORT_MACRO_NAME ENGINE_INPUT_EXPORTS
            EXPORT_FILE_NAME ${ENGINE_INPUT_INCLUDE_DIR}/EngineInputExport.generate.h
            STATIC_DEFINE ENGINE_INPUT_EXPORTS_BUILT_AS_STATIC
    )
endif(BUILD_SHARED_LIBS)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER VisReal/Engine/Modules)

# expose include headers
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_INPUT_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC Engine.Core)
