cmake_minimum_required(VERSION 3.17)

add_subdirectory(${PROJECT_SOURCE_DIR}/Library/DirectXShaderCompiler)

target_link_libraries(${PROJECT_NAME} DirectXShaderCompiler)