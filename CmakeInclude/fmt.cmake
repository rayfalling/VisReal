cmake_minimum_required(VERSION 3.14)

add_subdirectory(${CMAKE_SOURCE_DIR}/Library/fmt)

set_target_properties(fmt PROPERTIES FOLDER VisReal/Engine/Library)
