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

    Shader(const std::string &vertexShader, const std::string &fragmentShader);
    ~Shader();
};

}; // namespace GFX
