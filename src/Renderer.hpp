#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace GFX {

class Renderer{
private:
    GLFWwindow *window;

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    static void error_callback(int error, const char *description);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

public:
    // basic drawing
    void clear(GLint mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    void clearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

    // window info
    bool shouldClose();
    void swapBuffers();

    Renderer();
    ~Renderer();
};

}; // namespace GFX
