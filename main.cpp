#include <iostream>
#include "src/GFX.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Camera camera = GFX::Camera(&renderer);

    GFX::Model model = GFX::Model("obj/armadillo.obj")

    GFX::Shader shader = GFX::Shader("defaultShader");
    GFX::ShaderWatcher shaderWatcher = GFX::ShaderWatcher();
    shaderWatcher.attach(&shader);

    shader.updateUniform("transform", glm::mat4(1.0f));

    struct MyVertex {
        glm::vec3 pos;
    };

    std::vector<unsigned int> vertexTable = { 3 };

    GFX::VertexStack stack = GFX::VertexStack<MyVertex>({
        { { 0.5, -0.5, 0.0 } },
        { { -0.5, -0.5, 0.0 } },
        { { 0.0, 0.5, 0.0 } }
    }, vertexTable);

    auto draw = [&](float deltaTime) {
        shaderWatcher.checkShaders();

        camera.handleMouse(&renderer);
        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        renderer.clear();
        renderer.clearColor(0.2, 0.3, 0.3, 1.0);

        stack.draw(&shader);
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
