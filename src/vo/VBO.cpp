#include "VBO.hpp"

namespace GFX {

GLuint VBO::getVBO() {
    return this->vbo;
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::setBufferData(float *data, size_t size) {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

/* FIXME */ 
void VBO::setAttribPointer(GLint index, GLint size, int stride, int offset) {
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(index);
}

VBO::VBO() {
    glGenBuffers(1, &this->vbo);
}

VBO::~VBO() {
    glDeleteBuffers(1, &this->vbo);
}

}; // namespace GFX
