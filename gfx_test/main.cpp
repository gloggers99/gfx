#include <gfx/GFX.hpp>

#include <glm/ext/matrix_transform.hpp>

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Shader shader = GFX::Shader("defaultShader");
    
    GFX::Camera camera = GFX::Camera();
    GFX::Model model = GFX::Model("obj/test.obj");

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));
    transform = glm::translate(transform, glm::vec3(0.0f, -5.0f, -5.0f));

    shader.updateUniform("transform", transform);

    auto draw = [&](float deltaTime) {
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        model.draw(&shader);

    };

    renderer.loop(draw);

    return 0;
}

