/**
 * Created by rayfalling on 2020/8/30.
 * 
 * Typedef file for project.
 * Use for cross platform data type.
 * Windows platform definition to override generic definition.
 * */
#pragma once

#ifndef VISREAL_WINDOWS_PLATFORM_H
#define VISREAL_WINDOWS_PLATFORM_H

#include "GenericPlatformTypes.h"

namespace Engine::Core::Types {
    /**
    * Windows specific types
    **/
    struct FWindowsPlatformTypes : public GenericPlatformTypes {
#ifdef Platform_x64
        typedef unsigned __int64 USIZE_T;
        typedef __int64          SIZE_T;
#else
        typedef unsigned long USIZE_T;
        typedef long		  SIZE_T;
#endif
    };

    typedef FWindowsPlatformTypes FPlatformTypes;
}
#endif //VISREAL_WINDOWS_PLATFORM_H
