#include "../src/GFX.hpp"

#include <GLFW/glfw3.h>
#include <string>

int main() {
    GFX::Renderer renderer = GFX::Renderer();

    GFX::Shader shader = GFX::Shader(
        R"(
            #version 330

            layout (location = 0) in vec3 aPos;

            void main() {
                gl_Position = vec4(aPos, 1.0);
            }
        )", 
        R"(
            #version 330

            out vec4 FragColor;

            void main() {
                FragColor = vec4(1.0, 0.0, 0.0, 1.0);
            }
        )"
    );

    /*
    float vertices[] = {
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.0, 0.5, 0.0
    };
    */

    float vertices[] = {
        0.5, 0.5, 0.0,
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0,
        -0.5, 0.5, 0.0
    };

    unsigned int indices[] = {
        0, 1, 3,
        2, 3, 1
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

    auto draw = [&renderer, &shader, &vao](int deltaTime) {
        renderer.clear();
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader.use();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        renderer.swapBuffers();
    };

    renderer.loop(draw);

    return 0;
}
