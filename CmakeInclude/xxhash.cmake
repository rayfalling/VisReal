cmake_minimum_required(VERSION 3.14)

set(XXHASH_BUILD_XXHSUM OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/xxhash/cmake_unofficial)

set(XXHASH_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/libs/xxhash)
set_target_properties(xxhash PROPERTIES FOLDER VisReal/Engine/libs)
