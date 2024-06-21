#include "../src/Renderer.hpp"
#include <GLFW/glfw3.h>

int main() {
    GFX::Renderer renderer = GFX::Renderer();

    while (!renderer.shouldClose()) {
        renderer.clear();
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
        renderer.swapBuffers();
        glfwPollEvents();
    }

    return 0;
}
