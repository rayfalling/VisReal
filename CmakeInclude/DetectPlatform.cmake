cmake_minimum_required(VERSION 3.14)

message("Detect Platform: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

if (MSVC)
    # set character set unicode to make TCHAR is alias of wchar_t
    add_definitions(-DUNICODE -D_UNICODE)
    add_compile_definitions(MSVC)
    add_compile_options(/MP)
    if (CMAKE_CL_64)
        set(DXC_BUILD_ARCH "x64")
    else (CMAKE_CL_64)
        set(DXC_BUILD_ARCH "Win32")
    endif (CMAKE_CL_64)
    message("Set DXC_BUILD_ARCH ${DXC_BUILD_ARCH}")
    if (BUILD_SHARED_LIBS)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    endif (BUILD_SHARED_LIBS)

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DEBUG")             # 调试包不优化
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /NDEBUG")    # release包优化
elseif (MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")             # 调试包不优化
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")    # release包优化
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