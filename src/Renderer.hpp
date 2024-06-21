#pragma once

#include <functional>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace GFX {

class Renderer{
private:
    // glfw stuff
    GLFWwindow *window;

    // deltatime variables
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float currentFrame = 0.0f;

    // callbacks
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    static void error_callback(int error, const char *description);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

public:
    void clear(GLint mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    void clearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

    bool shouldClose();
    void swapBuffers();

    void loop(std::function<void(int)>);

    Renderer();
    ~Renderer();
};

}; // namespace GFX
