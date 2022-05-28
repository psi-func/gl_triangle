//
// Created by PsiFunction on 25.05.2022.
//

#ifndef OPENGL_COURSE_MESH_H
#define OPENGL_COURSE_MESH_H

#include <GL/glew.h>

class Mesh {
public:
    Mesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
    ~Mesh() = default;
    void RenderMesh() const;
private:
    GLuint VAO{0}, VBO{0}, IBO{0}, indexCount{0};
};


#endif //OPENGL_COURSE_MESH_H
