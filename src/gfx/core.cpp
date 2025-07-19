#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <gfx/core.hpp>
#include <gfx/window_spec.hpp>

#include <memory>
#include <stdexcept>

namespace gfx {

    void core::error_callback(int error, const char *description) {
        throw std::runtime_error(description);
    }

    core::core(const window_spec &spec) 
        : window({nullptr, &glfwDestroyWindow}) {

        if (!glfwInit())
            throw std::runtime_error("gfx: failed to initialize glfw!");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwWindowHint(GLFW_FLOATING, 1);

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

        glfwMakeContextCurrent(this->window.get());
        gladLoadGL(glfwGetProcAddress);
        
        //  TODO: Utilize some kind of logging software, maybe hermes (my own) 
        //        like the original gfx code.
        printf("GLFW platform: %s\n", glfwGetPlatform() == GLFW_PLATFORM_WAYLAND ? "Wayland" : "X11");

        while (!glfwWindowShouldClose(this->window.get())) {
            glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(this->window.get());
            glfwPollEvents();
        }
    }

    core::~core() {
        // Everything that needs to happen to clean up
        // gfx will happen here.

        glfwTerminate();
    }

} // namespace gfx
