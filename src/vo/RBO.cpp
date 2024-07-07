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
    int w, h;
    renderer->getSize(&w, &h);

    glRenderbufferStorage(GL_RENDERBUFFER, type, w, h);
}

RBO::RBO() {
    glGenRenderbuffers(1, &this->rbo);
}

RBO::~RBO() {
    glDeleteRenderbuffers(1, &this->rbo);
}

} // namespace GFX