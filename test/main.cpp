#include "../src/GFX.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Shader shader = GFX::Shader("defaultShader");
    GFX::Camera camera = GFX::Camera();

    // the definition of a vertex is subject to change.
    std::vector<GFX::Vertex> vertices = {
        {{0.5, -0.5, 0.0}},
        {{-0.5, -0.5, 0.0}},
        {{0.0, 0.5, 0.0}}
    };

    GFX::VertexStack stack = GFX::VertexStack(vertices);

    auto draw = [&](float deltaTime) {
        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));
        stack.draw(&shader);
    };

    renderer.loop(draw);

    return 0;
}

