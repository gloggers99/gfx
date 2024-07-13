#include "RBO.hpp"

namespace GFX {

GLuint RBO::get() {
    return this->rbo;
}

void RBO::bind() {
    glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
}

void RBO::unbind() {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RBO::setRenderBufferStorage(GLenum type, Renderer *renderer) {
    auto size = renderer->getSize();

    glRenderbufferStorage(GL_RENDERBUFFER, type, size.first, size.second);
}

RBO::RBO() {
    glGenRenderbuffers(1, &this->rbo);
}

RBO::~RBO() {
    glDeleteRenderbuffers(1, &this->rbo);
}

} // namespace GFX