#include "../src/Renderer.hpp"
#include <GLFW/glfw3.h>

int main() {
    GFX::Renderer renderer = GFX::Renderer();

    auto draw = [&renderer](int deltaTime) {
        renderer.clear();
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
        renderer.swapBuffers();
    };

    renderer.loop(draw);

    return 0;
}
