#include <iostream>

#include "src/GFX.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Camera camera = GFX::Camera(&renderer);

    GFX::Model model = GFX::Model("obj/armadillo.obj");

    GFX::Shader defaultShader = GFX::Shader("lightingShader");

    GFX::ShaderWatcher shaderWatcher = GFX::ShaderWatcher();
    shaderWatcher.attach(&defaultShader);

    defaultShader.updateUniform("transform", glm::mat4(1.0f));

    defaultShader.updateUniform("lightPos", glm::vec3(5.0, 2.0, -5.0));
    defaultShader.updateUniform("lightColor", glm::vec3(1.0, 1.0, 1.0));
    defaultShader.updateUniform("objectColor", glm::vec3(1.0, 0.5, 0.31));

    renderer.hideCursor();
    bool showCursor = false;

    renderer.keyMap.add(
            {GLFW_KEY_ESCAPE, GLFW_PRESS, 0}, [&]() {
                showCursor ? renderer.hideCursor() : renderer.showCursor();
                showCursor = !showCursor;
            }
    );
    renderer.keyMap.add(
            {GLFW_KEY_Q, GLFW_PRESS, GLFW_MOD_ALT}, [&]() {
                renderer.quit();
            }
    );

    auto draw = [&](float deltaTime) {
        shaderWatcher.checkShaders();

        camera.handleMouse(&renderer);
        defaultShader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        renderer.clear();
        renderer.clearColor(0.1, 0.1, 0.1, 1.0);

        model.draw(&defaultShader);

        if (renderer.getKey(GLFW_KEY_W))
            camera.move(GFX::Direction::FORWARD, deltaTime * 2.5f);
        if (renderer.getKey(GLFW_KEY_S))
            camera.move(GFX::Direction::BACKWARD, deltaTime * 2.5f);
        if (renderer.getKey(GLFW_KEY_A))
            camera.move(GFX::Direction::LEFT, deltaTime * 2.5f);
        if (renderer.getKey(GLFW_KEY_D))
            camera.move(GFX::Direction::RIGHT, deltaTime * 2.5f);
    };


    renderer.loop(draw);

    return 0;
}
