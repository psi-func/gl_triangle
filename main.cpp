#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Window.h"
#include "Mesh.h"

#include <vector>
// window dimensions
constexpr GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.f;


bool direction = true;
float triOffset = 0.f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

float curAngle = 0.f;

std::vector<Mesh> meshList;
std::vector<Shader> shaderList;

// Vertex shader
static const std::string vShader = "Shaders/vert-shader.glsl";
// Fragment shader
static const std::string fShader = "Shaders/frag-shader.glsl";

void createObjects() {
    unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2,
    };

    GLfloat vertices[] = {
            -1.f, -1.f, 0.f, // NOLINT
            0.f, -1.f, 1.f, // NOLINT
            1.f, -1.f, 0.f,  // NOLINT
            0.f, 1.f, 0.f,   // NOLINT
    };

    meshList.emplace_back(vertices, indices, 12, 12);
}

void createShaders() {
    shaderList.emplace_back(vShader, fShader);
}

int main(int argc, char const *argv[])
{
    Window::initEnviron();
    auto mainwindow =  Window::CreateWindow(WIDTH, HEIGHT, "simple window").value();
    createObjects();
    createShaders();


    glm::mat4 projection = glm::perspective(45.f, static_cast<GLfloat>(mainwindow.getBufferWidth())/static_cast<GLfloat>(mainwindow.getBufferHeight()), 0.1f, 100.f);

    // loop until window closed
    while (!mainwindow.shouldClose())
    {
        // get and handle user input events
        glfwPollEvents();

        if (direction)
        {
            triOffset += triIncrement;
        }
        else
        {
            triOffset -= triIncrement;
        }

        if (std::abs(triOffset) >= triMaxOffset)
        {
            direction = !direction;

        }

        curAngle += 0.1f;

        // clear window
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto& shaderProgram = shaderList[0];
        shaderProgram.useShader();

        glm::mat4 model(1.f);
//        model = glm::translate(model, glm::vec3(triOffset, 0.f, 0.f));
        model = glm::translate(model, glm::vec3(0.f, 0.f, -2.f));
        model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.f, 1.f, 0.f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4, 1.f));

        shaderProgram.setModelUniform(model);
        shaderProgram.setProjectionUniform(projection);

        const auto& mesh = meshList[0];
        mesh.RenderMesh();

        glUseProgram(0);

        mainwindow.swapBuffers();
    }

    // glfwDestroyWindow(mainwindow);
    // glfwTerminate();
    return 0;
}
