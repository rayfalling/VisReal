#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include "Entry.h"
#include "Container/TArray.h"

int main() {
    Engine::InitEngine();

    /* test area */
    TArray<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };
    array.Add(9);
    std::cout << array[3] << std::endl;
    array.RemoveRange(0,8);
    std::cout << array[0] << std::endl;
//
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
