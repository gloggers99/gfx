#pragma once

#include "IVO.hpp"

#include "glad/gl.h"
#include "../Renderer.hpp"

namespace GFX {

class RBO : IVO {
private:
    GLuint rbo;
public:
    GLuint get() override;

    void bind() override;
    void unbind() override;

    void setRenderBufferStorage(GLenum type, Renderer *renderer);

    RBO();
    ~RBO();
};

}; // namespace GFX

