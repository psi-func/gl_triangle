//
// Created by PsiFunction on 23.05.2022.
//

#include "Window.h"
#include <iostream>

Window::Window(GLFWwindow* windowPtr) :
    _window(windowPtr, glfwDestroyWindow)
{
    glfwGetFramebufferSize(_window.get(), &bufferWidth, &bufferHeight);

    // set context to GLEW to use
    glfwMakeContextCurrent(_window.get());

    glewExperimental = GL_TRUE;
    if (glewInit())
    {
        std::cerr << "GLEW init fails!\n";
        glfwTerminate();
    }
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, bufferWidth, bufferHeight);
}

void Window::initEnviron() {
    //  init glfw
    //  init glfw
    if (!glfwInit())
    {
        std::cerr << "GLFW init fails!\n";
        glfwTerminate();
        return;
    }

    // setup glfw window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile = No backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

}

std::optional<Window> Window::CreateWindow(GLint width, GLint  height, const std::string& title) {
    GLFWwindow *window = glfwCreateWindow(width, height,
                                              title.data(), nullptr, nullptr);
    if (!window)
    {
        std::cerr << "GLFW window creation fails!";
        glfwTerminate();
        return std::nullopt;
    }

    return std::optional<Window>(window);
}
