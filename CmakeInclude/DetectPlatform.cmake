cmake_minimum_required(VERSION 3.17)

message("Detect Platform: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

if (MSVC)
    # set character set unicode to make TCHAR is alias of wchar_t
    add_definitions(-DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS)
    if (CMAKE_CL_64)
        set(DXC_BUILD_ARCH "x64")
    else (CMAKE_CL_64)
        set(DXC_BUILD_ARCH "Win32")
    endif (CMAKE_CL_64)
    message("Set DXC_BUILD_ARCH ${DXC_BUILD_ARCH}")
    if (BUILD_SHARED_LIBS)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    endif (BUILD_SHARED_LIBS)

    add_compile_definitions(MSVC)
    add_compile_definitions(OVERRIDE_PLATFORM_HEADER_NAME=Windows)

    add_compile_options(/MP /wd4819 /wd5045 /wd4711)
    set(CMAKE_C_FLAGS_DEBUG "/ZI /Ob0 /Od /RTC1")
    set(CMAKE_CXX_FLAGS_DEBUG "/ZI /Ob0 /Od /RTC1")
elseif (MSVC)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
endif (MSVC)

# judge platform
if (CMAKE_CL_64)
    set(TARGET_ARCH x64)
    message(STATUS "Set Platform x64")
else (CMAKE_CL_64)
    set(TARGET_ARCH x86)
    message(STATUS "Set Platform x86")
endif (CMAKE_CL_64)