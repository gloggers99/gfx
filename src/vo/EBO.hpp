#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace GFX {

class EBO {
private:
    GLuint ebo;
public:
    GLuint getEBO();
    void bind();
    void unbind();
    void setBufferData(unsigned int *indices, size_t size);

    EBO();
    ~EBO();
};

}; // namespace GFX
