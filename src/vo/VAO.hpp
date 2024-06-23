#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace GFX {

class VAO {
private:
    GLuint vao;
public:
    GLuint getVAO();
    void bind();
    void unbind();

    VAO();
    ~VAO();
};

}; // namespace GFX
