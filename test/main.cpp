#include "../src/GFX.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Shader shader = GFX::Shader(
        R"(
            #version 330

            layout (location = 0) in vec3 aPos;

            uniform mat4 transform;
            uniform mat4 camera;

            void main() {
                gl_Position = camera * transform * vec4(aPos, 1.0);
            }
        )",
        R"(
            #version 330

            out vec4 FragColor;

            uniform vec4 color;

            void main() {
                FragColor = color;
            }
        )"
    );

    float vertices[] = {
        0.5, 0.5, 0.0,
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0,
        -0.5, 0.5, 0.0
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GFX::VAO vao = GFX::VAO();
    GFX::VBO vbo = GFX::VBO();
    GFX::EBO ebo = GFX::EBO();

    vao.bind();
    vbo.bind();
    vbo.setBufferData(vertices, sizeof(vertices));
    vbo.setAttribPointer(0, 3, 3 * sizeof(float), 0);
    ebo.bind();
    ebo.setBufferData(indices, sizeof(indices));
    vao.unbind();

    GFX::Camera camera = GFX::Camera();

    renderer.hideCursor();

    auto draw = [&renderer, &camera, &shader, &vao](int deltaTime) {
        renderer.clear();
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader.use();
        shader.updateUniform("color", 1.0, 1.0, 0.0, 1.0);

        glm::mat4 cameraMatrix = camera.createCameraMatrix(&renderer);
        shader.updateUniform("camera", cameraMatrix);

        vao.bind();

        glm::mat4 transformMatrix = glm::mat4(1.0);
        transformMatrix = glm::translate(transformMatrix, glm::vec3(0.0, 0.0, 0.5));
        shader.updateUniform("transform", transformMatrix);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        transformMatrix = glm::mat4(1.0);
        transformMatrix = glm::translate(transformMatrix, glm::vec3(0.0, 0.0, -0.5));
        shader.updateUniform("transform", transformMatrix);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        
        transformMatrix = glm::mat4(1.0);
        transformMatrix = glm::translate(transformMatrix, glm::vec3(-0.5, 0.0, 0.0));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
        shader.updateUniform("transform", transformMatrix);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

         
        transformMatrix = glm::mat4(1.0);
        transformMatrix = glm::translate(transformMatrix, glm::vec3(0.0, -0.5, 0.0));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
        shader.updateUniform("transform", transformMatrix);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);       

        transformMatrix = glm::mat4(1.0);
        transformMatrix = glm::translate(transformMatrix, glm::vec3(0.0, 0.5, 0.0));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
        shader.updateUniform("transform", transformMatrix);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   

        transformMatrix = glm::mat4(1.0);
        transformMatrix = glm::translate(transformMatrix, glm::vec3(0.5, 0.0, 0.0));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
        shader.updateUniform("transform", transformMatrix);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        renderer.swapBuffers();

        // input
        camera.handleMouse(&renderer);

        if (renderer.getKey(GLFW_KEY_W) == GLFW_PRESS)
            camera.move(GFX::Direction::FORWARD, deltaTime * 0.1f);
        if (renderer.getKey(GLFW_KEY_S) == GLFW_PRESS)
            camera.move(GFX::Direction::BACKWARD, deltaTime * 0.1f);
        if (renderer.getKey(GLFW_KEY_A) == GLFW_PRESS)
            camera.move(GFX::Direction::LEFT, deltaTime * 0.1f);
        if (renderer.getKey(GLFW_KEY_D) == GLFW_PRESS)
            camera.move(GFX::Direction::RIGHT, deltaTime * 0.1f);
    };

    renderer.loop(draw);

    return 0;
}
