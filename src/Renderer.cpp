#include "Renderer.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#if not defined(__MINGW32__)
#include <imgui.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#endif

#include <iostream>
#include <stdexcept>

namespace GFX {

void Renderer::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Renderer::error_callback(int error, const char *description) {
    std::cerr << "Error " << error << ": " << description << std::endl;
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

void Renderer::enableWireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::disableWireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

void Renderer::loop(const std::function<void(float)>& loopFunction) {
    while (!this->shouldClose()) {
#if not defined(__MINGW32__)
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
#endif
        this->currentFrame = glfwGetTime();
        this->deltaTime = this->currentFrame - this->lastFrame;
        this->lastFrame = this->currentFrame;
        this->clear();
        loopFunction(this->deltaTime);
#if not defined(__MINGW32__)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
        this->swapBuffers();
        glfwPollEvents();
    }
}

Renderer::Renderer(std::string windowName) : windowName(std::move(windowName)) {
    this->log("initializing renderer...");

    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    glfwSetErrorCallback(Renderer::error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_FLOATING, 1);

    this->window = glfwCreateWindow(640, 480, this->windowName.c_str(), nullptr, nullptr);

    if (!this->window)
        throw std::runtime_error("Failed to create window");

    glfwMakeContextCurrent(this->window);
    glfwSetFramebufferSizeCallback(this->window, Renderer::framebuffer_size_callback);
    glfwSetKeyCallback(this->window, Renderer::key_callback);
    gladLoadGL(glfwGetProcAddress);
    
    glViewport(0, 0, 640, 480);
    glEnable(GL_DEPTH_TEST);

    // setup imgui
#if not defined(__MINGW32__)
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init();
#endif
    this->log("renderer initialized");
}

Renderer::~Renderer() {
#if not defined(__MINGW32__)
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(this->window);
    glfwTerminate();
#endif
}

}; // namespace GFX
