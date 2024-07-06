#include <iostream>
#include "src/GFX.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Camera camera = GFX::Camera(&renderer);

    GFX::Model model = GFX::Model("./obj/test2.obj");
    GFX::Shader shader = GFX::Shader("lightingShader");
    GFX::ShaderWatcher shaderWatcher = GFX::ShaderWatcher();
    shaderWatcher.attach(&shader);

    shader.updateUniform("transform", glm::mat4(1.0f));

    shader.updateUniform("lightPos", glm::vec3(1.2f, 1.2f, 2.0f));
    shader.updateUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.updateUniform("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));


    auto draw = [&](float deltaTime) {
        shaderWatcher.checkShaders();

        camera.handleMouse(&renderer);
        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));
        shader.updateUniform("viewPos", camera.getCameraPos());

        renderer.clear();
        renderer.clearColor(0.2, 0.3, 0.3, 1.0);
        model.draw(&shader);
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
