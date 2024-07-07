#include "FBO.hpp"
#include "../Renderer.hpp"

namespace GFX {

GLuint FBO::get() {
    return this->fbo;
}

void FBO::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
}

void FBO::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::attachRenderBuffer(GFX::RBO rbo) {
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo.get());
}

bool FBO::isComplete() {
    return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}

FBO::FBO() {
    glGenFramebuffers(1, &this->fbo);
}

FBO::~FBO() {
    glDeleteFramebuffers(1, &this->fbo);
}

} // namespace GFX