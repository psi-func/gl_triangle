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
#include <array>

class Window {
public:
    explicit Window(GLFWwindow* window);
    ~Window();
    Window(Window&&) noexcept = default;
    Window& operator=(Window&&) noexcept = default;

    [[nodiscard]] GLint  getBufferWidth() const { return bufferWidth; }
    [[nodiscard]] GLint  getBufferHeight() const { return bufferHeight; }
    bool shouldClose() { return glfwWindowShouldClose(_window); }
    void swapBuffers() { glfwSwapBuffers(_window); }

    static void initEnviron();
    static std::optional<Window> CreateWindow(GLint width, GLint  height, const std::string& title);

private:
    GLFWwindow* _window;
//    GLint _width, _height;
    GLint bufferWidth{}, bufferHeight{};

    std::array<bool, 1024> keys{};

    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
};




#endif //OPENGL_COURSE_WINDOW_H
