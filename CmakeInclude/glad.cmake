cmake_minimum_required(VERSION 3.14)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/glad)

# Detect 64bit python interpreter if arch is AMD64
if (${TARGET_ARCH} STREQUAL "x64")
    option(-A x64)
endif (${TARGET_ARCH} STREQUAL "x64")

set(GLAD_API "gl=,gles=" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
set(GLAD_SPEC "gl" CACHE STRING "Name of the spec")

set_target_properties(glad glad-generate-files PROPERTIES FOLDER libs)
