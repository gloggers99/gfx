#include "../src/GFX.hpp"
#include <GLFW/glfw3.h>

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Shader shader = GFX::Shader(
        R"(
            #version 330

            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoord;

            uniform mat4 transform;
            uniform mat4 camera;

            out vec2 TexCoord;

            void main() {
                gl_Position = camera * transform * vec4(aPos, 1.0);
                TexCoord = aTexCoord;
            }
        )",
        R"(
            #version 330

            out vec4 FragColor;
            in vec2 TexCoord;

            uniform sampler2D Texture;

            void main() {
                FragColor = texture(Texture, TexCoord);
            }
        )"
    );

    GFX::Camera camera = GFX::Camera();

    renderer.hideCursor();
    
    float vertices[] = {
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.0, 0.5, 0.0
    };
    GFX::Cube cube = GFX::Cube(shader);

    auto draw = [&renderer, &camera, &shader, &cube](int deltaTime) {
        renderer.clear();
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader.use();
        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));
        shader.updateUniform("transform", glm::mat4(1.0f));

        cube.setTransform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(glfwGetTime()) * 50, glm::vec3(0.0f, 1.0f, 1.0f));
        cube.draw();

        renderer.swapBuffers();

        // input
        //camera.handleMouse(&renderer);
        
        float cameraSpeed = 0.01 * deltaTime;

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
