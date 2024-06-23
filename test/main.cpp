#include "../src/GFX.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();

    GFX::Shader shader = GFX::Shader();

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
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        renderer.swapBuffers();
    };

    renderer.loop(draw);

    return 0;
}
