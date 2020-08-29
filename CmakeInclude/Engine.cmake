cmake_minimum_required(VERSION 3.1)

add_subdirectory(${PROJECT_SOURCE_DIR}/Engine)

target_link_libraries(${PROJECT_NAME} Engine)