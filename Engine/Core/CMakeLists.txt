cmake_minimum_required(VERSION 3.17)

# Project Name
project("Engine.Core" C CXX)

# Set CXX flags
set(CMAKE_CXX_STANDARD 17)

if (!MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")             # 调试包不优化
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG ")    # release包优化
else (!MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/DEBUG")             # 调试包不优化
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /NDEBUG ")    # release包优化
    add_compile_definitions("MSVC")
endif ()

add_subdirectory(Marco)
add_subdirectory(Object)
add_subdirectory(Render)
add_subdirectory(Type)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(
        ${PROJECT_NAME}
        INTERFACE
        "Engine.Core.Marco"
        "Engine.Core.Object"
        "Engine.Core.Render"
        "Engine.Core.Type"
)