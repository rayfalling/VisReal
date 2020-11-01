cmake_minimum_required(VERSION 3.14)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/spdlog)

set(SPDLOG_ENABLE_PCH ON)
set(SPDLOG_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/libs/spdlog/include)
set(SPDLOG_WCHAR_SUPPORT ON)
set(SPDLOG_WCHAR_FILENAMES ON)

if (BUILD_SHARED_LIBS)
    set(SPDLOG_BUILD_SHARED ON)
endif(BUILD_SHARED_LIBS)

set_target_properties(spdlog PROPERTIES FOLDER libs)