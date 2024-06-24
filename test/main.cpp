#include "../src/GFX.hpp"

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

            uniform vec4 color;

            void main() {
                FragColor = color;
            }
        )"
    );

    float vertices[] = {
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.0, 0.5, 0.0
    };

    GFX::VAO vao = GFX::VAO();
    GFX::VBO vbo = GFX::VBO();

    vao.bind();
    vbo.bind();
    vbo.setBufferData(vertices, sizeof(vertices));
    vbo.setAttribPointer(0, 3, 3 * sizeof(float), 0);
    vao.unbind();

    auto draw = [&renderer, &shader, &vao](int deltaTime) {
        renderer.clear();
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader.use();
        shader.updateUniform("color", 1.0, 1.0, 0.0, 1.0);
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        renderer.swapBuffers();
    };

    renderer.loop(draw);

    return 0;
}
