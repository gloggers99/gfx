#include "EBO.hpp"

namespace GFX {

GLuint EBO::get() {
    return this->ebo;
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::setBufferData(unsigned int *indices, size_t size) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

EBO::EBO() {
    glGenBuffers(1, &this->ebo);
}

EBO::~EBO() {
    glDeleteBuffers(1, &this->ebo);
}

}; // namespace GFX
