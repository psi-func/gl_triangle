#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstring>
#include <iostream>

// window dimensions
constexpr GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.f;
GLuint VAO, VBO, shader, uniformModel;

bool direction = true;
float triOffset = 0.f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

// Vertex shader
static const char *vShader =
    "#version 330\n"
    "layout (location = 0) in vec3 pos;\n"
    "uniform mat4 model;\n"
    "void main()\n"
    "{\n"
    "gl_Position = model * vec4(pos, 1.0);\n"
    "}\n";

// Fragment shader
static const char *fShader =
    "#version 330\n"
    "out vec4 colour;\n"
    "void main()\n"
    "{\n"
    "colour = vec4(1.0, 0.0, 1.0, 1.0);\n"
    "}\n";

void createTriangle()
{
    GLfloat vertices[] = {
        -1.f, -1.f, 0.f, // NOLINT
        1.f, -1.f, 0.f,  // NOLINT
        0.f, 1.f, 0.f,   // NOLINT
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // unbind things
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);
    const GLchar *theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(theShader, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error compiling " << shaderType << " shader: " << eLog << std::endl;
        return;
    }

    glAttachShader(theProgram, theShader);
    return;
}

void CompileShaders()
{
    shader = glCreateProgram();

    if (!shader)
    {
        std::cerr << "Error creating shader program!\n";
        return;
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error linking program: " << eLog << std::endl;
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error linking program: " << eLog << std::endl;
        return;
    }

    uniformModel = glGetUniformLocation(shader, "model");
}

int main(int argc, char const *argv[])
{

    //  init glfw
    if (!glfwInit())
    {
        std::cerr << "GLFW init fails!\n";
        glfwTerminate();
        return 1;
    }

    // setup glfw window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile = No backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *mainwindow = glfwCreateWindow(WIDTH, HEIGHT, "test window", nullptr, nullptr);
    if (!mainwindow)
    {
        std::cerr << "GLFW window creation fails!";
        glfwTerminate();
        return 1;
    }

    // Get buffer size info
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainwindow, &bufferWidth, &bufferHeight);

    // set context to GLEW to use
    glfwMakeContextCurrent(mainwindow);

    // allow modern extension feature
    glewExperimental = GL_TRUE;

    if (glewInit())
    {
        std::cerr << "GLEW init fails!\n";
        glfwDestroyWindow(mainwindow);
        glfwTerminate();
        return 1;
    }

    glViewport(0, 0, bufferWidth, bufferHeight);

    createTriangle();
    CompileShaders();

    // loop until window closed
    while (!glfwWindowShouldClose(mainwindow))
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

        // clear window
        glClearColor(1.f, 0.5f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glm::mat4 model(1.f);
        model = glm::translate(model, glm::vec3(triOffset, 0.f, 0.f));
        model = glm::rotate(model, 45 * toRadians, glm::vec3(0.f, 0.f, 1.f));
        model = glm::scale(model, glm::vec3(0.5f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(mainwindow);
    }

    // glfwDestroyWindow(mainwindow);
    // glfwTerminate();
    return 0;
}
