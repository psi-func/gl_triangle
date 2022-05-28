//
// Created by PsiFunction on 23.05.2022.
//

#include "Window.h"
#include <iostream>
#include <algorithm>

Window::Window(GLFWwindow* windowPtr) :
    _window(windowPtr)
{
    keys.fill(false);

    glfwGetFramebufferSize(_window, &bufferWidth, &bufferHeight);

    // set context to GLEW to use
    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    if (glewInit())
    {
        std::cerr << "GLEW init fails!\n";
        glfwTerminate();
    }
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, bufferWidth, bufferHeight);

    glfwSetWindowUserPointer(_window, this);
}

void Window::initEnviron() {
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
    if (!window) {
        std::cerr << "GLFW window creation fails!";
        glfwTerminate();
        return std::nullopt;
    }

    return std::optional<Window>(window);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    auto theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024) {

        if (action == GLFW_PRESS) {
            theWindow->keys[key] = true;
#ifdef _DEBUG
            std::cout << "Pressed: " << key << '\n';
#endif
        }
        else if (action == GLFW_RELEASE){
            theWindow->keys[key] = false;
#ifdef _DEBUG
            std::cout << "Released: " << key << '\n';
#endif
        }
    }

}

Window::~Window() {
    glfwDestroyWindow(_window);
    glfwTerminate();

}
