#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <string>

namespace GFX {

class Shader {
private:
    GLuint vertexShader, fragmentShader;
    GLuint shaderProgram;

public:
    void use();

    Shader(const std::string &vertexShader = R"(
            #version 330

            layout (location = 0) in vec3 aPos;

            void main() {
                gl_Position = vec4(aPos, 1.0);
            }
        )", const std::string &fragmentShader = R"(
            #version 330

            out vec4 FragColor;

            void main() {
                FragColor = vec4(1.0, 0.0, 0.0, 1.0);
            }
        )");
    ~Shader();
};

}; // namespace GFX
