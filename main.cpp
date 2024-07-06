#include <iostream>
#include "src/GFX.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Camera camera = GFX::Camera();

    GFX::Model model = GFX::Model("./obj/test2.obj");
    GFX::Shader shader = GFX::Shader("defaultShader");

    shader.updateUniform("transform", glm::mat4(1.0f));

    auto draw = [&](float deltaTime) {
        camera.handleMouse(&renderer);
        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        renderer.clear();
        renderer.clearColor(0.2, 0.3, 0.3, 1.0);
        model.draw(&shader);
    };

    renderer.loop(draw);

    return 0;
}
