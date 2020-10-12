cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine.Core.Object" C CXX)

# include all header files
set("ENGINE_CORE_OBJECT_INCLUDE" ${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${ENGINE_CORE_OBJECT_INCLUDE})
aux_source_directory(Source ENGINE_CORE_OBJECT_SOURCE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_CORE_OBJECT_INCLUDE} ${ENGINE_CORE_OBJECT_SOURCE})

add_library(${PROJECT_NAME} ${ENGINE_CORE_OBJECT_INCLUDE} ${ENGINE_CORE_OBJECT_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# expose include headers
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_CORE_OBJECT_INCLUDE})

target_link_libraries(${PROJECT_NAME} "Engine.Core.Type")
