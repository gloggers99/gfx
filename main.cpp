#include <iostream>
#include "src/GFX.hpp"
#include "src/vo/FBO.hpp"
#include "src/vo/RBO.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Camera camera = GFX::Camera(&renderer);

    GFX::Model model = GFX::Model("obj/armadillo.obj");

    GFX::Shader defaultShader = GFX::Shader("defaultShader");
    GFX::Shader camShader = GFX::Shader("camShader");

    GFX::ShaderWatcher shaderWatcher = GFX::ShaderWatcher();
    shaderWatcher.attach(&defaultShader);
    shaderWatcher.attach(&camShader);

    //shader.updateUniform("transform", glm::mat4(1.0f));

    struct Vertex {
        glm::vec2 position;
        glm::vec2 texCoords;
    };

    GFX::VertexStack stack = GFX::VertexStack<Vertex>({
                    {{1.0, 1.0}, {1.0, 1.0}},
                    {{1.0, -1.0}, {1.0, 0.0}},
                    {{-1.0, 1.0}, {0.0, 1.0}},

                    {{1.0, -1.0}, {1.0, 0.0}},
                    {{-1.0, -1.0}, {0.0, 0.0}},
                    {{-1.0, 1.0}, {0.0, 1.0}}
    }, {2, 2});

    auto draw = [&](float deltaTime) {
        shaderWatcher.checkShaders();

        camera.handleMouse(&renderer);
        camShader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        renderer.clear();
        renderer.clearColor(0.1, 0.1, 0.1, 1.0);

        model.draw(&camShader);

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
