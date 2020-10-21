cmake_minimum_required(VERSION 3.17)

# Project Name
project("VisReal.Test" LANGUAGES C CXX)

# Make codecvt work for c++17
add_compile_definitions(_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)

# Set CXX flags
set(CMAKE_CXX_STANDARD 17)

set("ENGINE_TEST_INCLUDE_DIR" ${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${ENGINE_INCLUDE_DIR}/)
file(GLOB_RECURSE ENGINE_TEST_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/Include/*)
aux_source_directory(Source ENGINE_TEST_SOURCE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_INCLUDE} ${ENGINE_SOURCE})

# add executable before include library for test use
add_executable(${PROJECT_NAME} ${ENGINE_TEST_INCLUDE} ${ENGINE_TEST_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "test.main")

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Engine/Test)

# expose include headers
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_INCLUDE_DIR})

link_directories(${ENGINE_CORE_INCLUDE_DIR} ${ENGINE_RENDER_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} "Engine")
