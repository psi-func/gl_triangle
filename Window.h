//
// Created by PsiFunction on 23.05.2022.
//

#ifndef OPENGL_COURSE_WINDOW_H
#define OPENGL_COURSE_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <array>

class Window {
public:
    Window(GLint width, GLint  height, const std::string& title);
    ~Window();
    Window(Window&&) noexcept = default;
    Window& operator=(Window&&) noexcept = default;

    [[nodiscard]] GLint  getBufferWidth() const { return bufferWidth; }
    [[nodiscard]] GLint  getBufferHeight() const { return bufferHeight; }
    bool shouldClose() { return glfwWindowShouldClose(_window); }
    void swapBuffers() { glfwSwapBuffers(_window); }

    static void initEnviron();;

private:
    GLFWwindow* _window{nullptr};
//    GLint _width, _height;
    GLint bufferWidth{}, bufferHeight{};

    std::array<bool, 1024> keys{};

    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
};




#endif //OPENGL_COURSE_WINDOW_H
