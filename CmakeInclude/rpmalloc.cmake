cmake_minimum_required(VERSION 3.17)

option(VISREAL_ENABLE_MALLOC_STATS "Enables statistics for rpmalloc" OFF)

add_subdirectory(${CMAKE_SOURCE_DIR}/Library/rpmalloc)

set(RPMALLOC_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/Library/rpmalloc/src/rpmalloc)
set_target_properties(rpmalloc PROPERTIES FOLDER VisReal/Engine/Library)
