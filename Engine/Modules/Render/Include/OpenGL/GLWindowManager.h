/**
 * Created by rayfalling on 2020/8/29.
 *
 * OpenGL window manager
 * Singleton mode to avoid multi window
 * */

#pragma once

#ifndef VISREAL_GL_WINDOW_MANAGER_H
#define VISREAL_GL_WINDOW_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Object/ISingletonObject.h"
#include "CoreTypes.h"
#include "VersionCheck.h"

using namespace Engine::Core;

namespace Engine::Render::OPENGL {
    class GLWindowManager : public ISingletonObject<GLWindowManager> {
    public:
        void SetWindowSize(int width, int height);
        //TODO methods here


    private:
        GLWindowManager();

        void InitOpenGL(int width, int height);
        void InitOpenGL(int width, int height, GLVersion version);

        /* Current window to draw */
        GLFWwindow* window;
    };
}

#endif //VISREAL_GL_WINDOW_MANAGER_H
