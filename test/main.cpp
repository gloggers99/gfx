#include "../src/GFX.hpp"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

int main() {
    GFX::Renderer renderer = GFX::Renderer();

    GFX::Camera camera = GFX::Camera();

    //renderer.hideCursor();
    
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    GFX::Shader testShader = GFX::Shader("defaultShader");
    GFX::Shader lightingShader = GFX::Shader("lightingShader");

    GFX::Cube cube1 = GFX::Cube(lightingShader);
    GFX::Cube cube2 = GFX::Cube(testShader);
    float r = 0.5f;
    float g = 0.5f;
    float b = 0.5f;

    bool compiled = true;

    auto draw = [&compiled, &renderer, &camera, &lightPos, &cube1, &cube2, &r, &g, &b, &testShader, &lightingShader](float deltaTime) {
        ImGui::Begin("testmenu");

        ImGui::SliderFloat("red", &r, 0.0f, 1.0f);
        ImGui::SliderFloat("green", &g, 0.0f, 1.0f);
        ImGui::SliderFloat("blue", &b, 0.0f, 1.0f);
        if (ImGui::Button("Reset")) {
            r = 0.5f;
            g = 0.5f;
            b = 0.5f;
        }
        if (ImGui::Button("Recompile Shader")) {
            std::cout << "recompiling shader\n";
            if (!lightingShader.recompile()) {
                compiled = false;
            } else {
                compiled = true;
            }
        }
        if (!compiled)
            ImGui::Text("Shader failed to compile!!");

        ImGui::End();

        renderer.clear();
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);

        testShader.updateUniform("transform", glm::mat4(1.0f));
        testShader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        lightingShader.updateUniform("objectColor", r, g, b);
        lightingShader.updateUniform("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.updateUniform("lightPos", lightPos);
        lightingShader.updateUniform("viewPos", camera.getCameraPos());
        lightingShader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, glm::radians((float)glfwGetTime() * 100), glm::vec3(1.0f, 1.0f, 0.0f));
        cube1.setTransform(transform);
        cube1.draw();

        lightPos.x = sin(glfwGetTime()) * 2;
        lightPos.y = sin(glfwGetTime()) * 2;
        lightPos.z = cos(glfwGetTime()) * 2;
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, lightPos);
        transform = glm::scale(transform, glm::vec3(0.2f));
        cube2.setTransform(transform);
        cube2.draw();

        // input
        camera.handleMouse(&renderer);
    
        float cameraSpeed = 2.5 * deltaTime;

        if (renderer.getKey(GLFW_KEY_W) == GLFW_PRESS)
            camera.move(GFX::Direction::FORWARD, cameraSpeed);
        if (renderer.getKey(GLFW_KEY_S) == GLFW_PRESS)
            camera.move(GFX::Direction::BACKWARD, cameraSpeed);
        if (renderer.getKey(GLFW_KEY_A) == GLFW_PRESS)
            camera.move(GFX::Direction::LEFT, cameraSpeed);
        if (renderer.getKey(GLFW_KEY_D) == GLFW_PRESS)
            camera.move(GFX::Direction::RIGHT, cameraSpeed);
    };

    renderer.loop(draw);

    return 0;
}
