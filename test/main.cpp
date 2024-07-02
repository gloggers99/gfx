#include "../src/GFX.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Shader shader = GFX::Shader("lightingShader");
    GFX::ShaderWatcher shaderWatcher = GFX::ShaderWatcher();
    shaderWatcher.attach(shader);
    GFX::Camera camera = GFX::Camera();
    GFX::Model model = GFX::Model("obj/test.obj");

    auto draw = [&](float deltaTime) {
        shaderWatcher.checkShaders();

        camera.handleMouse(&renderer);
        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        shader.updateUniform("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
        shader.updateUniform("viewPos", camera.getCameraPos());
        shader.updateUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.updateUniform("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

        shader.updateUniform("transform", glm::mat4(1.0f));

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

