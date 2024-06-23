#include "../src/Renderer.hpp"
#include "../src/Shader.hpp"

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

    float vertices[] = {
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.0, 0.5, 0.0
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    auto draw = [&renderer, &shader, vao](int deltaTime) {
        renderer.clear();
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        renderer.swapBuffers();
    };

    renderer.loop(draw);

    return 0;
}
