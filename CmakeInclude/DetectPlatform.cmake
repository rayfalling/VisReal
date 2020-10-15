cmake_minimum_required(VERSION 3.14)

message("Detect Platform: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

if (MSVC)
    # set character set unicode to make TCHAR is alias of wchar_t
    add_definitions(-DUNICODE -D_UNICODE)
    add_compile_definitions(MSVC)
    if (CMAKE_CL_64)
        set(DXC_BUILD_ARCH "x64")
    else (CMAKE_CL_64)
        set(DXC_BUILD_ARCH "Win32")
    endif (CMAKE_CL_64)
    message("Set DXC_BUILD_ARCH ${DXC_BUILD_ARCH}")
endif (MSVC)

# judge platform
if (CMAKE_CL_64)
    set(TARGET_ARCH x64)
    message(STATUS "Set Platform x64")
    add_compile_definitions("Platform_x64")
else (CMAKE_CL_64)
    set(TARGET_ARCH x86)
    message(STATUS "Set Platform x86")
    add_compile_definitions("Platform_x86")
endif (CMAKE_CL_64)