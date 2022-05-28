//
// Created by PsiFunction on 23.05.2022.
//

#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string& vShaderPath, const std::string& fShaderPath) {
    compileShaders(
                Shader::readShaderFromFile(vShaderPath),
                   Shader::readShaderFromFile(fShaderPath)
                   );
}


std::string Shader::readShaderFromFile(const std::string& path) {
    std::string shaderCode;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::badbit);
    try {
        shaderFile.open(path, std::ios::in);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        shaderCode = shaderStream.str();
    }
    catch(const std::ifstream::failure& e) {
        std::cerr << "Shader file " << path << " cannot be read\n";
    }

    return shaderCode;
}

void Shader::addShader(std::string shaderCode, GLenum shaderType) const {
    GLuint theShader = glCreateShader(shaderType);
    const GLchar *theCode = shaderCode.data();
    const auto codeLength = static_cast<GLint>(shaderCode.size());

    glShaderSource(theShader, 1, std::addressof(theCode), std::addressof(codeLength));
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

    glAttachShader(this->_shaderId, theShader);
}

void Shader::compileShaders(const std::string& vShader,const std::string& fShader) {
    _shaderId = glCreateProgram();

    if (!_shaderId) {
        std::cerr << "Error creating shader program!\n";
        return;
    }

    addShader(vShader, GL_VERTEX_SHADER);
    addShader(fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(_shaderId);
    glGetProgramiv(_shaderId, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(_shaderId, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error linking program: " << eLog << std::endl;
        return;
    }

    glValidateProgram(_shaderId);
    glGetProgramiv(_shaderId, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(_shaderId, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error linking program: " << eLog << std::endl;
        return;
    }

    _modelUniform = glGetUniformLocation(_shaderId, "model");
    _projectionUniform = glGetUniformLocation(_shaderId, "projection");


}

void Shader::setModelUniform(const glm::mat4 &mat) const {
    glUniformMatrix4fv(getModelLocation(), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setProjectionUniform(const glm::mat4 &mat) const {
    glUniformMatrix4fv(getProjectionLocation(), 1, GL_FALSE, glm::value_ptr(mat));
}


