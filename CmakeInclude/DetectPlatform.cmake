cmake_minimum_required(VERSION 3.14)

message("Detect Platform: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

if (MSVC)
    if(CMAKE_CL_64)
        set(DXC_BUILD_ARCH "x64")
    elseif(CMAKE_CL_64)
        set(DXC_BUILD_ARCH "Win32")
    endif(CMAKE_CL_64)
endif (MSVC)

# judge platform
IF (CMAKE_CL_64)
    set(TARGET_ARCH x64)
    message(STATUS "Set Platform Win64")
    add_compile_definitions("Platform_Win64")
ELSE (CMAKE_CL_64)
    set(TARGET_ARCH x86)
    message(STATUS "Set Platform Win32")
    add_compile_definitions("Platform_Win32")
ENDIF (CMAKE_CL_64)