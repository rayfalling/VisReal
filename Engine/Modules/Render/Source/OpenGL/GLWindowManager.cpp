/**
 * Created by rayfalling on 2020/8/29.
 * */

#include "OpenGL/GLWindowManager.h"

namespace Engine::Render::OpenGL {

	GLWindowManager::GLWindowManager() {
		//        glfwInit();
		//        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//
		//        GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
		//        if (window == nullptr)
		//        {
		//            std::cout << "Failed to create GLFW window" << std::endl;
		//            glfwTerminate();
		//            return -1;
		//        }
		//        glfwMakeContextCurrent(window);
		//        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		//        {
		//            std::cout << "Failed to initialize GLAD" << std::endl;
		//            return -1;
		//        }
		//        glViewport(0, 0, 800, 600);
	}

	void GLWindowManager::InitOpenGL(int width, int height) {
		glfwInit();
		//        // commit this to use max support opengl version
		//        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Check if window is already created */
		if (window != nullptr) {
			return;
		}
		window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
		if (window == nullptr) {
			//            std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			//            std::cout << "Failed to initialize GLAD" << std::endl;
		}

		//TODO check max opengl version
		GLint majorVersion;
		GLint minorVersion;

		glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
		glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);

		glViewport(0, 0, 800, 600);
		while (!glfwWindowShouldClose(window)) {
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void GLWindowManager::SetWindowSize(int width, int height) {
		if (window == nullptr)
			return;
		glViewport(0, 0, width, height);
	}

	void GLWindowManager::InitOpenGL(int width, int height, GLVersion version) {

	}
}
