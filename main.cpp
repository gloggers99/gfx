#include <iostream>

#include "src/GFX.hpp"

#include <imgui.h>

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Camera camera = GFX::Camera(renderer);

    GFX::Model light = GFX::Model("obj/test2.obj");
    light.transform.scale({0.5, 0.5, 0.5});
    GFX::Model model = GFX::Model("obj/untitled.obj");
    GFX::Material material = GFX::Material("obj/untitled.mtl");
    model.material = material;

    GFX::Shader lightingShader = GFX::Shader("lightingShader");
    GFX::Shader defaultShader = GFX::Shader("camShader");

    GFX::ShaderWatcher shaderWatcher = GFX::ShaderWatcher();
    shaderWatcher.attach(&lightingShader);

    glm::vec3 lightPosition = glm::vec3(5.0f, 2.0, -5.0);

    lightingShader.updateUniform("lightColor", glm::vec3(1.0, 1.0, 1.0));
    lightingShader.updateUniform("objectColor", glm::vec3(1.0, 1.0, 1.0));

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
        ImGui::Text("test");

        shaderWatcher.checkShaders();

        camera.handleMouse();
        lightingShader.updateUniform("camera", camera.createCameraMatrix());
        defaultShader.updateUniform("camera", camera.createCameraMatrix());

        renderer.clear();
        renderer.clearColor(0.1, 0.1, 0.1, 1.0);

        lightingShader.updateUniform("lightPos", lightPosition);
        model.draw(lightingShader);

        lightPosition.x = std::cos(glfwGetTime()) * 10;
        lightPosition.y = std::sin(glfwGetTime()) * 10;
        lightPosition.z = std::sin(glfwGetTime()) * 10;

        light.transform.setTranslation(lightPosition);

        defaultShader.updateUniform("lightPos", lightPosition);
        light.draw(defaultShader);

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
