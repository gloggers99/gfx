#pragma once

#include <GLFW/glfw3.h>

#include <memory>
#include <optional>

#include "window_spec.hpp"

namespace gfx {

using glfw_window = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;

///
/// The "core" of gfx
///
/// Originally gfx.hpp was a metaclass which imported
/// every other class and feature of gfx. Now we will
/// stick to object oriented programming.
///
class core {
    /// Triggered on GLFW error
    static void error_callback(int error, const char *description);

    glfw_window window;

public:
    core(const window_spec &spec = {});
    ~core();
};

} // namespace gfx
