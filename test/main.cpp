#include <gfx/GFX.hpp>
#include <glm/ext/matrix_transform.hpp>

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Shader shader = GFX::Shader("defaultShader");
    GFX::ShaderWatcher shaderWatcher = GFX::ShaderWatcher();
    shaderWatcher.attach(shader);
    GFX::Camera camera = GFX::Camera();
    GFX::Model model = GFX::Model("obj/test.obj");

    auto draw = [&](float deltaTime) {
        shaderWatcher.checkShaders();

        camera.handleMouse(&renderer);
        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        shader.updateUniform("transform", glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f)));

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

