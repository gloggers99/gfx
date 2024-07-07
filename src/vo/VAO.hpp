#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "IVO.hpp"

namespace GFX {

class VAO : IVO {
private:
    GLuint vao;
public:
    GLuint get() override;
    void bind() override;
    void unbind() override;

    VAO();
    ~VAO();
};

}; // namespace GFX
