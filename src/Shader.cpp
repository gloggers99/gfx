#include "Shader.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

namespace GFX {

void Shader::use() {
    glUseProgram(this->shaderProgram);
}

Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader) {
    int success;
    char buffer[512];

    // vertex shader
    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexSource = vertexShader.c_str();
    glShaderSource(this->vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(this->vertexShader);
    glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(this->vertexShader, 512, nullptr, buffer);
        std::cerr << "\nVertex shader failed to compile:\n\n" << buffer << "\n";
    }

    // fragment shader
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentSource = fragmentShader.c_str();
    glShaderSource(this->fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(this->fragmentShader);
    glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(this->fragmentShader, 512, nullptr, buffer);
        std::cerr << "\nFragment shader failed to compile:\n\n" << buffer << "\n";
    }

    // create program
    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, this->vertexShader);
    glAttachShader(this->shaderProgram, this->fragmentShader);
    glLinkProgram(this->shaderProgram);
    glGetShaderiv(this->shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->shaderProgram, 512, nullptr, buffer);
        std::cerr << "\nShader compiling error:\n" << buffer << "\n";
    }
}

Shader::~Shader() {
    glDeleteProgram(this->shaderProgram);
}

}; // namespace GFX
