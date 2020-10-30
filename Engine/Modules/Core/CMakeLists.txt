cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine.Core" C CXX)

# Set CXX flags
set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

set("ENGINE_CORE_INCLUDE_DIR" ${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${ENGINE_CORE_INCLUDE_DIR}/)
file(GLOB_RECURSE ENGINE_CORE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/Include/*)
aux_source_directory(Source ENGINE_CORE_SOURCE)
aux_source_directory(Source/Container ENGINE_CORE_SOURCE)
aux_source_directory(Source/Hash ENGINE_CORE_SOURCE)
aux_source_directory(Source/Logger ENGINE_CORE_SOURCE)
aux_source_directory(Source/Marco ENGINE_CORE_SOURCE)
aux_source_directory(Source/Math ENGINE_CORE_SOURCE)
aux_source_directory(Source/Object ENGINE_CORE_SOURCE)
aux_source_directory(Source/Platform ENGINE_CORE_SOURCE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_CORE_INCLUDE} ${ENGINE_CORE_SOURCE})

add_library(${PROJECT_NAME} ${LIB_TYPE} ${ENGINE_CORE_INCLUDE} ${ENGINE_CORE_SOURCE})
if (BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_CORE_SHARED)
    GENERATE_EXPORT_HEADER(
            ${PROJECT_NAME}
            BASE_NAME ENGINE_CORE
            EXPORT_MACRO_NAME ENGINE_CORE_EXPORTS
            EXPORT_FILE_NAME ${ENGINE_CORE_INCLUDE_DIR}/EngineCoreExport.generate.h
            STATIC_DEFINE ENGINE_CORE_EXPORTS_BUILT_AS_STATIC
    )
endif(BUILD_SHARED_LIBS)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Engine)

target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_CORE_INCLUDE_DIR})

link_directories(${ENGINE_CORE_INCLUDE_DIR} ${SPDLOG_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog PRIVATE Threads::Threads)