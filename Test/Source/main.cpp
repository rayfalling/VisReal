//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include "Entry.h"
#include "TestTMap.h"
#include "TestTArray.h"

int main() {
    Engine::InitEngine();
    TestTArray();
    TestTMap();

//    glfwInit();
//    // commit this to use max support opengl version
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
//    if (window == nullptr) {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    //TODO check max opengl version
//    GLint majorVersion;
//    GLint minorVersion;
//
////    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
////    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
////    std::cout << majorVersion << "." << minorVersion << std::endl;
//
//    glViewport(0, 0, 800, 600);
//    while (!glfwWindowShouldClose(window)) {
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
    return 0;
}
