cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine.Core.Type" C CXX)

# Make codecvt work for c++17
add_compile_definitions(_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)

# include all header files
set("ENGINE_CORE_TYPE_INCLUDE" ${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${ENGINE_CORE_TYPE_INCLUDE})
aux_source_directory(Source ENGINE_CORE_TYPE_SOURCE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_CORE_TYPE_INCLUDE} ${ENGINE_CORE_TYPE_SOURCE})

add_library(${PROJECT_NAME} SHARED ${ENGINE_CORE_TYPE_INCLUDE} ${ENGINE_CORE_TYPE_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/EHsc")
endif ()

# expose include headers
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_CORE_TYPE_INCLUDE})
