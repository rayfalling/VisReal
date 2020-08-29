cmake_minimum_required(VERSION 3.1)

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glad)

set(GLAD_API "gl=,gles=" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
set(GLAD_SPEC "gl" CACHE STRING "Name of the spec")

target_link_libraries(${PROJECT_NAME} glad)