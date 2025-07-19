#include <GLFW/glfw3.h>
#include <gfx/gfx.hpp>
#include <gfx/window_spec.hpp>

#include <memory>
#include <stdexcept>

namespace gfx {

core::core(const window_spec &spec) 
    : window({nullptr, &glfwDestroyWindow}) {

    if (!glfwInit())
        throw std::runtime_error("gfx: failed to initialize glfw!");

    GLFWwindow *window = glfwCreateWindow(
        spec.window_width,
        spec.window_height, 
        spec.window_title.data(), 
        nullptr, 
        nullptr
    );

    if (!window)
        throw std::runtime_error("gfx: failed to create window!");

    this->window = {
        window, 
        &glfwDestroyWindow
    };
    
    //  TODO: Everything
}

core::~core() {
    // Everything that needs to happen to clean up
    // gfx will happen here.

    glfwTerminate();
}


} // namespace gfx
