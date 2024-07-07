#pragma once

#include <glad/gl.h>

namespace GFX {

class IVO {
public:
    virtual GLuint get() = 0;
    virtual void bind() = 0;
    virtual void unbind() = 0;
};

} // namespace GFX

