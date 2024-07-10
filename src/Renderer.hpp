#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <string>
#include <iostream>
#include <hermes/hermes.hpp>

#include "KeyMap.hpp"

namespace GFX {

class Renderer{
private:
    Hermes::Log<char> log = Hermes::Log("GFX::Renderer");

    std::string windowName;

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

    /**
     * Initialize GLFW
     */
    void initGLFW();

    /**
     * Create the GLFW window
     *
     * @param windowName Name for the window to have
     * @param width Window width
     * @param height Window height
     * @param fullscreen Fullscreen toggle
     */
    void createWindow(const std::string &windowName = "gfx",
                      bool fullscreen = false,
                      int width = 640,
                      int height = 480);

public:
    // keyMap being public should be fine
    KeyMap keyMap;

    /**
     * Quit the renderer
     */
    void quit();

    /**
     * Gets the current mode of the key inputted
     *
     * @param key Key to check (ex. GLFW_KEY_W)
     */
    GLint getKey(int key);

    /**
     * Get the window size and put it in two pointers TODO: ALSO CHANGE THIS!!!
     *
     * @param width Width of the window
     * @param height Height of the window
     */
    void getSize(int *width, int *height);

    /**
     * Get the cursor position and put it into two double pointers TODO: CHANGE THIS!!!
     *
     * @param xpos X position of the mouse
     * @param ypos Y position of the mouse
     */
    void getCursorPos(double *xpos, double *ypos);

    /**
     * Enable wireframe drawing
     */
    void enableWireframe();

    /**
     * Disable wireframe drawing
     */
    void disableWireframe();

    /**
     * Show the cursor
     */
    void showCursor();

    /**
     * Hide the cursor
     */
    void hideCursor();

    /**
     * glClear(); on the underlying renderer window
     *
     * @param mask The buffer bits to clear
     */
    void clear(GLint mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    /**
     * Set the color buffer bit
     *
     * @param r Red value
     * @param g Green value
     * @param b Blue value
     * @param a Alpha value
     */
    void clearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

    /**
     * @return glfwWindowShouldClose(); on the underlying renderer window
     */
    bool shouldClose();

    /**
     * Run glfwSwapBuffers(); on the underlying renderer window
     */
    void swapBuffers();

    /**
     * Start the renderer loop using the function inputted
     *
     * @param loopFunction Function to loop
     */
    void loop(const std::function<void(float)> &loopFunction);

    /**
     * Create a Renderer instance
     *
     * @param windowName Name for the GLFW window instance
     * @param fullscreen Toggle to make the window fullscreen
     */
    explicit Renderer(std::string windowName = "gfx", bool fullscreen = false);
    ~Renderer();
};

}; // namespace GFX
