//
// Created by PsiFunction on 23.05.2022.
//

#ifndef OPENGL_COURSE_WINDOW_H
#define OPENGL_COURSE_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <optional>

class Window {
public:
    ~Window() = default;
    Window(Window&&) noexcept = default;
    Window& operator=(Window&&) noexcept = default;

    GLint  getBufferWidth() { return bufferWidth; }
    GLint  getBufferHeight() { return bufferHeight; }
    bool shouldClose() { return glfwWindowShouldClose(_window.get()); }
    void swapBuffers() { glfwSwapBuffers(_window.get()); }
    Window(GLFWwindow* window);

    static void initEnviron();
    static std::optional<Window> CreateWindow(GLint width, GLint  height, const std::string& title);

private:

private:
    using windowPtr = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;
    windowPtr _window;
//    GLint _width, _height;
    int bufferWidth, bufferHeight;
};




#endif //OPENGL_COURSE_WINDOW_H
