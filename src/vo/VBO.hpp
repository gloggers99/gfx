#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "IVO.hpp"

namespace GFX {

class VBO : IVO {
private:
    GLuint vbo;
public:
    GLuint get() override;
    void bind() override;
    void unbind() override;
    void setBufferData(const void *data, size_t size);
    void setAttribPointer(GLint index, GLint size, int stride, int offset);

    VBO();
    ~VBO();
};

}; // namespace GFX
