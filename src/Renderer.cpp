#include "Renderer.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

namespace GFX {

void Renderer::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Renderer::error_callback(int error, const char *description) {
    std::cerr << "Error: " << description << std::endl;
}

void Renderer::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

GLint Renderer::getKey(int key) {
    return glfwGetKey(this->window, key);
}

void Renderer::getSize(int *width, int *height) {
    glfwGetFramebufferSize(this->window, width, height);
}

void Renderer::getCursorPos(double *xpos, double *ypos) {
    glfwGetCursorPos(this->window, xpos, ypos);
}

void Renderer::showCursor() {
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Renderer::hideCursor() {
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Renderer::clear(GLint mask) {
    glClear(mask);
}

void Renderer::clearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

bool Renderer::shouldClose() {
    return glfwWindowShouldClose(this->window);
}

void Renderer::swapBuffers() {
    glfwSwapBuffers(this->window);
}

void Renderer::loop(std::function<void(int)> loopFunction) {
    while (!this->shouldClose()) {
        this->currentFrame = glfwGetTime();
        this->deltaTime = this->currentFrame - this->lastFrame;
        this->lastFrame = this->currentFrame;
        loopFunction(1);
        glfwPollEvents();
    }
}

Renderer::Renderer() {
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    glfwSetErrorCallback(Renderer::error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_FLOATING, 1);

    this->window = glfwCreateWindow(640, 480, "gfx", nullptr, nullptr);

    if (!this->window)
        throw std::runtime_error("Failed to create window");

    glfwMakeContextCurrent(this->window);
    glfwSetFramebufferSizeCallback(this->window, Renderer::framebuffer_size_callback);
    glfwSetKeyCallback(this->window, Renderer::key_callback);
    gladLoadGL(glfwGetProcAddress);
    
    glViewport(0, 0, 640, 480);
    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

}; // namespace GFX
