#include "VAO.hpp"

namespace GFX {

GLuint VAO::getVAO() {
    return this->vao;
}

void VAO::bind() {
    glBindVertexArray(this->vao);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

VAO::VAO() {
    glGenVertexArrays(1, &this->vao);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &this->vao);
}

}; // namespace GFX
