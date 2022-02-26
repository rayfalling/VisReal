cmake_minimum_required(VERSION 3.17)

set(SPDLOG_ENABLE_PCH ON)
set(SPDLOG_WCHAR_SUPPORT ON)
set(SPDLOG_WCHAR_FILENAMES ON)
set(SPDLOG_FMT_EXTERNAL ON)

if (BUILD_SHARED_LIBS)
    set(SPDLOG_BUILD_SHARED ON)
endif(BUILD_SHARED_LIBS)

set(SPDLOG_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/Library/spdlog/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/Library/spdlog)

set_target_properties(spdlog PROPERTIES FOLDER VisReal/Engine/Library)