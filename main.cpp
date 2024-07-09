#include <iostream>

#include "src/GFX.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Camera camera = GFX::Camera(renderer);

    GFX::Model model = GFX::Model("obj/armadillo.obj");
    GFX::Model cube = GFX::Model("obj/test2.obj");
    cube.transform.scale({0.5, 0.5, 0.5});

    GFX::Shader lightingShader = GFX::Shader("lightingShader");
    GFX::Shader defaultShader = GFX::Shader("camShader");

    GFX::ShaderWatcher shaderWatcher = GFX::ShaderWatcher();
    shaderWatcher.attach(&lightingShader);

    glm::vec3 lightPosition = glm::vec3(5.0f, 2.0, -5.0);

    lightingShader.updateUniform("transform", glm::mat4(1.0f));

    lightingShader.updateUniform("lightColor", glm::vec3(1.0, 1.0, 1.0));
    lightingShader.updateUniform("objectColor", glm::vec3(1.0, 0.5, 0.31));

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

        camera.handleMouse(renderer);
        lightingShader.updateUniform("camera", camera.createCameraMatrix(&renderer));
        defaultShader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        renderer.clear();
        renderer.clearColor(0.1, 0.1, 0.1, 1.0);

        lightingShader.updateUniform("lightPos", lightPosition);
        model.draw(&lightingShader);

        lightPosition.x = std::cos(glfwGetTime()) * 10;
        lightPosition.y = std::sin(glfwGetTime()) * 10;
        lightPosition.z = std::sin(glfwGetTime()) * 10;

        cube.transform.setTranslation(lightPosition);

        defaultShader.updateUniform("lightPos", lightPosition);

        cube.draw(&defaultShader);

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
