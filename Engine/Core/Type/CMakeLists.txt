cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine.Core.Type" C CXX)

# include all header files
set("ENGINE_CORE_TYPE_INCLUDE" ${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${ENGINE_CORE_TYPE_INCLUDE})
aux_source_directory(Source ENGINE_CORE_TYPE_SOURCE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_CORE_TYPE_INCLUDE} ${ENGINE_CORE_TYPE_SOURCE})

add_library(${PROJECT_NAME} ${ENGINE_CORE_TYPE_INCLUDE} ${ENGINE_CORE_TYPE_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_CORE_TYPE_INCLUDE})
