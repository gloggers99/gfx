#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "IVO.hpp"

namespace GFX {

class EBO : IVO {
private:
    GLuint ebo;
public:
    GLuint get() override;
    void bind() override;
    void unbind() override;
    void setBufferData(unsigned int *indices, size_t size);

    EBO();
    ~EBO();
};

}; // namespace GFX
