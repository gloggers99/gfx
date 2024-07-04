#include <gfx/GFX.hpp>
#include <GLFW/glfw3.h>

#include <glm/ext/matrix_transform.hpp>

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Shader shader = GFX::Shader("defaultShader");
    
    GFX::Camera camera = GFX::Camera();
    GFX::Model libertyStatue = GFX::Model("obj/test2.obj");
    //GFX::Model ogre = GFX::Model("obj/test.obj");

    glm::mat4 transform = glm::mat4(1.0f);

    shader.updateUniform("transform", transform);

    auto draw = [&](float deltaTime) {
        camera.handleMouse(&renderer);
        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);

        libertyStatue.draw(&shader);
        //ogre.draw(&shader);

        float camSpeed = 2.5f * deltaTime;
        if (renderer.getKey(GLFW_KEY_W))
            camera.move(GFX::Direction::FORWARD, camSpeed);
        if (renderer.getKey(GLFW_KEY_S))
            camera.move(GFX::Direction::BACKWARD, camSpeed);
        if (renderer.getKey(GLFW_KEY_A))
            camera.move(GFX::Direction::LEFT, camSpeed);
        if (renderer.getKey(GLFW_KEY_D))
            camera.move(GFX::Direction::RIGHT, camSpeed);

    };

    renderer.loop(draw);

    return 0;
}

