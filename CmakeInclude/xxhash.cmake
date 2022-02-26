cmake_minimum_required(VERSION 3.17)

set(XXHASH_BUILD_XXHSUM OFF)
set(XXHASH_BUNDLED_MODE OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/Library/xxhash/cmake_unofficial)

set(XXHASH_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/Library/xxhash)
set_target_properties(xxhash PROPERTIES FOLDER VisReal/Engine/Library)
