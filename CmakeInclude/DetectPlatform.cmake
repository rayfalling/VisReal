cmake_minimum_required(VERSION 3.14)

message("Detect Platform: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

if (MSVC)
    # set character set unicode to make TCHAR is alias of wchar_t
    add_definitions(-DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(MSVC)
    if (CMAKE_CL_64)
        set(DXC_BUILD_ARCH "x64")
    else (CMAKE_CL_64)
        set(DXC_BUILD_ARCH "Win32")
    endif (CMAKE_CL_64)
    message("Set DXC_BUILD_ARCH ${DXC_BUILD_ARCH}")
    if (BUILD_SHARED_LIBS)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    endif (BUILD_SHARED_LIBS)

    add_compile_definitions(OVERRIDE_PLATFORM_HEADER_NAME=Windows)

    add_compile_options(/MP /wd4819 /wd5045 /wd4711)
    set(CMAKE_C_FLAGS_DEBUG "/ZI /Ob0 /Od /RTC1 /DEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "/ZI /Ob0 /Od /RTC1 /DEBUG")
elseif (MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif (MSVC)

# judge platform
if (CMAKE_CL_64)
    set(TARGET_ARCH x64)
    message(STATUS "Set Platform x64")
else (CMAKE_CL_64)
    set(TARGET_ARCH x86)
    message(STATUS "Set Platform x86")
endif (CMAKE_CL_64)