cmake_minimum_required(VERSION 3.14)

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/DirectXShaderCompiler)

target_link_libraries(${PROJECT_NAME} DirectXShaderCompiler)