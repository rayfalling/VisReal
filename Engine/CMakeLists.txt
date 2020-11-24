cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine" VERSION 1.0.0 LANGUAGES C CXX)

# Make codecvt work for c++17
add_compile_definitions(_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)

# Set CXX flags
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Modules)

set("ENGINE_INCLUDE_DIR" ${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${ENGINE_INCLUDE_DIR}/)
file(GLOB_RECURSE ENGINE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/Include/*)
aux_source_directory(Source ENGINE_SOURCE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_INCLUDE} ${ENGINE_SOURCE})

add_library(${PROJECT_NAME} ${LIB_TYPE} ${ENGINE_INCLUDE} ${ENGINE_SOURCE})
if (BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_SHARED)
    GENERATE_EXPORT_HEADER(
            ${PROJECT_NAME}
            BASE_NAME ENGINE
            EXPORT_MACRO_NAME ENGINE_EXPORTS
            EXPORT_FILE_NAME ${ENGINE_INCLUDE_DIR}/EngineExport.generate.h
            STATIC_DEFINE ENGINE_EXPORTS_BUILT_AS_STATIC
    )
endif(BUILD_SHARED_LIBS)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER VisReal/Engine)

# expose include headers
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC "Engine.Core" "Engine.Render" "Engine.Event")
