cmake_minimum_required(VERSION 3.17)

# Set CXX flags
set(CMAKE_CXX_STANDARD 17)

add_library(
    rpmalloc ${LIB_TYPE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rpmalloc/rpmalloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rpmalloc/rpmalloc.h
)

target_include_directories(
    rpmalloc PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rpmalloc
)

set_property(TARGET rpmalloc PROPERTY C_STANDARD 11)

IF (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(rpmalloc PRIVATE -Wno-unused-variable)
endif ()

if (NOT MSVC)
    target_compile_definitions(rpmalloc PRIVATE -D_GNU_SOURCE)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # rpmalloc uses GCC builtin "__builtin_umull_overflow" with ENABLE_VALIDATE_ARGS,
    # which is only available starting with GCC 5
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU" AND CMAKE_C_COMPILER_VERSION VERSION_LESS 5)
        set(ENABLE_VALIDATE_ARGS OFF)
    else ()
        set(ENABLE_VALIDATE_ARGS ON)
    endif()
    target_compile_definitions(
        rpmalloc PRIVATE -DENABLE_ASSERTS=1 -DENABLE_VALIDATE_ARGS=${ENABLE_VALIDATE_ARGS}
    )
endif()

if (VISREAL_ENABLE_MALLOC_STATS)
    target_compile_definitions(rpmalloc PRIVATE -DENABLE_STATISTICS=1)
endif ()