/**
 * Created by rayfalling on 2020/10/20.
 * */

#ifndef VISREAL_MSVC_PLATFROM_H
#define VISREAL_MSVC_PLATFROM_H

namespace Engine::Core {
    #if _MSC_FULL_VER >= 191125507 && defined(__cpp_if_constexpr)
    #define PLATFORM_COMPILER_HAS_IF_CONSTEXPR 1
    #else
    #define PLATFORM_COMPILER_HAS_IF_CONSTEXPR 0
    #endif
}

#endif //VISREAL_MSVC_PLATFROM_H
