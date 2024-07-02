#include "../src/GFX.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Shader defaultShader = GFX::Shader("defaultShader");
    GFX::ShaderWatcher shaderWatcher = GFX::ShaderWatcher();
    shaderWatcher.attach(defaultShader);
    GFX::Camera camera = GFX::Camera();

    std::vector<GFX::Vertex> vertices = {
        {{0.5, -0.5, 0.0}},
        {{-0.5, -0.5, 0.0}},
        {{0.0, 0.5, 0.0}}
    };

    GFX::VertexStack stack = GFX::VertexStack(vertices);

    renderer.hideCursor();
    auto draw = [&](float deltaTime) {
        shaderWatcher.checkShaders();

        defaultShader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        renderer.clear();
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);

        stack.draw(&defaultShader);

        camera.handleMouse(&renderer);
    };
    renderer.loop(draw);

    return 0;
}
