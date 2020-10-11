cmake_minimum_required(VERSION 3.14)

message("Detect Platform: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

if (MSVC)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(TARGET_ARCH "x64")
        set(DXC_BUILD_ARCH "x64")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(TARGET_ARCH "Win32")
        set(DXC_BUILD_ARCH "Win32")
    endif()
endif (MSVC)