#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace GFX {

class VBO {
private:
    GLuint vbo;
public:
    GLuint getVBO();
    void bind();
    void unbind();
    void setBufferData(float *data, size_t size);
    void setAttribPointer(GLint index, GLint size, int stride, int offset);

    VBO();
    ~VBO();
};

}; // namespace GFX
