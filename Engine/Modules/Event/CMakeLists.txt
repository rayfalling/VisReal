cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine.Event" C CXX)

# Set CXX flags
set(CMAKE_CXX_STANDARD 17)

# include all header files
set("ENGINE_EVENT_INCLUDE_DIR" ${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${ENGINE_EVENT_INCLUDE_DIR})
file(GLOB_RECURSE ENGINE_EVENT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/Include/*)
aux_source_directory(Source ENGINE_EVENT_SOURCE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_EVENT_INCLUDE} ${ENGINE_EVENT_SOURCE})

add_library(${PROJECT_NAME} ${LIB_TYPE} ${ENGINE_EVENT_INCLUDE} ${ENGINE_EVENT_SOURCE})
if (BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_EVENT_SHARED)
    GENERATE_EXPORT_HEADER(
            ${PROJECT_NAME}
            BASE_NAME ENGINE_EVENT
            EXPORT_MACRO_NAME ENGINE_EVENT_EXPORTS
            EXPORT_FILE_NAME ${ENGINE_EVENT_INCLUDE_DIR}/EngineEventExport.generate.h
            STATIC_DEFINE ENGINE_EVENT_EXPORTS_BUILT_AS_STATIC
    )
endif(BUILD_SHARED_LIBS)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER VisReal/Engine/Modules)

# expose include headers
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_EVENT_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC Engine.Core)
