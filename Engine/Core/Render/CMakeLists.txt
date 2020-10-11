cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine.Core.Render" C CXX)
# include all header files
set("ENGINE_CORE_RENDER_INCLUDE" ${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${ENGINE_CORE_RENDER_INCLUDE})
include_directories(${ENGINE_CORE_RENDER_INCLUDE}/OpenGL)
include_directories(${ENGINE_CORE_OBJECT_HEADER} "Engine.Core.Object.out")
include_directories(${ENGINE_CORE_TYPE_HEADER} "Engine.Core.Type.out")
aux_source_directory(Source ENGINE_CORE_RENDER_SOURCE)
aux_source_directory(Source/OpenGL ENGINE_CORE_RENDER_SOURCE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_CORE_RENDER_INCLUDE} ${ENGINE_CORE_RENDER_SOURCE})

add_library(${PROJECT_NAME} ${ENGINE_CORE_RENDER_INCLUDE} ${ENGINE_CORE_RENDER_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# link opengl
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLAD_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIRS})
