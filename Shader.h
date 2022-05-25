//
// Created by PsiFunction on 23.05.2022.
//

#ifndef OPENGL_COURSE_SHADER_H
#define OPENGL_COURSE_SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

enum class MAT_TYPE {
    MODEL_MATRIX,
    PROJECTION_MATRIX,
};

class Shader {
public:
    Shader(std::string vShaderPath, std::string fShaderPath);
    ~Shader() = default;

    void useShader() const { glUseProgram(_shaderId); }
    [[nodiscard]] GLuint  getModelLocation() const { return _modelUniform; }
    [[nodiscard]] GLuint getProjectionLocation() const { return _projectionUniform; };
    void setModelUniform(const glm::mat4& mat) const;
    void setProjectionUniform(const glm::mat4& mat) const;


private:
    void addShader(std::string shaderCode, GLenum shaderType) const;
    void compileShaders(const std::string& vShader,const std::string& fShader);
    static std::string readShaderFromFile(const std::string& path);

    GLuint _shaderId{0};
    GLuint _modelUniform{0};
    GLuint _projectionUniform{0};

};


#endif //OPENGL_COURSE_SHADER_H
