/**
 * Created by rayfalling on 2020/8/29.
 *
 * OpenGL window manager
 * Singleton mode to avoid multi window
 * */

#pragma once

#ifndef VISREAL_GL_WINDOW_MANAGER_H
#define VISREAL_GL_WINDOW_MANAGER_H

#include "SingletonObject.h"
#include "Types.h"

namespace Engine::Render::OPENGL {
    class GLWindowManager : public ISingletonObject<GLWindowManager> {
    public:
        //TODO methods here

    private:
        GLWindowManager();

        void InitOpenGL(float width, float height, int8 major, int8 minor);
    };
}

#endif //VISREAL_GL_WINDOW_MANAGER_H
