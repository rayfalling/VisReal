cmake_minimum_required(VERSION 3.17)

# Detect 64bit python interpreter if arch is AMD64
if (${TARGET_ARCH} STREQUAL "x64")
    option(-A x64)
endif (${TARGET_ARCH} STREQUAL "x64")

add_subdirectory(${CMAKE_SOURCE_DIR}/Library/glad)

set_target_properties(glad glad-generate-files PROPERTIES FOLDER VisReal/Engine/Library)
