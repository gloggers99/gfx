#pragma once

#include "glad/gl.h"

#include "IVO.hpp"
#include "RBO.hpp"

namespace GFX {

class FBO : IVO {
private:
    GLuint fbo;

public:
    GLuint get() override;

    void bind() override;
    void unbind() override;

    void attachRenderBuffer(RBO rbo);
    bool isComplete();

    FBO();
    ~FBO();
};

} // namespace GFX
