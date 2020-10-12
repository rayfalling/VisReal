/**
 * Created by rayfalling on 2020/10/12.
 * */

#ifndef VISREAL_VERSION_CHECK_H
#define VISREAL_VERSION_CHECK_H

#include "Marcos.h"

namespace Engine::Render::OPENGL {
    struct GLVersion {
        int major;
        int minor;
    };

    DEPRECATED_WITH_TIPS(GLVersionNotSupport) [[maybe_unused]] const GLVersion GL_VERSION_1_0 = {1, 1};
    DEPRECATED_WITH_TIPS(GLVersionNotSupport) [[maybe_unused]] const GLVersion GL_VERSION_1_1 = {1, 1};
    DEPRECATED_WITH_TIPS(GLVersionNotSupport) [[maybe_unused]] const GLVersion GL_VERSION_1_2 = {1, 2};
    DEPRECATED_WITH_TIPS(GLVersionNotSupport) [[maybe_unused]] const GLVersion GL_VERSION_1_3 = {1, 3};
    DEPRECATED_WITH_TIPS(GLVersionNotSupport) [[maybe_unused]] const GLVersion GL_VERSION_1_4 = {1, 4};
    DEPRECATED_WITH_TIPS(GLVersionNotSupport) [[maybe_unused]] const GLVersion GL_VERSION_1_5 = {1, 5};
    DEPRECATED_WITH_TIPS(GLVersionNotSupport) [[maybe_unused]] const GLVersion GL_VERSION_2_0 = {2, 0};
    DEPRECATED_WITH_TIPS(GLVersionNotSupport) [[maybe_unused]] const GLVersion GL_VERSION_2_1 = {2, 1};
    DEPRECATED_WITH_TIPS(GLVersionNotSupport) [[maybe_unused]] const GLVersion GL_VERSION_3_0 = {3, 0};
    DEPRECATED_WITH_TIPS(GLVersionNotSupport) [[maybe_unused]] const GLVersion GL_VERSION_3_1 = {3, 1};
    DEPRECATED_WITH_TIPS(GLVersionNotSupport) [[maybe_unused]] const GLVersion GL_VERSION_3_2 = {3, 2};
    [[maybe_unused]] const GLVersion GL_VERSION_3_3 = {3, 3};
    [[maybe_unused]] const GLVersion GL_VERSION_4_0 = {4, 0};
    [[maybe_unused]] const GLVersion GL_VERSION_4_1 = {4, 1};
    [[maybe_unused]] const GLVersion GL_VERSION_4_2 = {4, 2};
    [[maybe_unused]] const GLVersion GL_VERSION_4_3 = {4, 3};
    [[maybe_unused]] const GLVersion GL_VERSION_4_4 = {4, 4};
    [[maybe_unused]] const GLVersion GL_VERSION_4_5 = {4, 5};
    [[maybe_unused]] const GLVersion GL_VERSION_4_6 = {4, 6};

    [[maybe_unused]] bool CheckGLVersion(GLVersion &version);
}
#endif //VISREAL_VERSION_CHECK_H
