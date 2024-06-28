#include "Shader.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stdexcept>
#include <string>

namespace GFX {

GLint Shader::getUniformLocation(const std::string &uniformName) {
    GLint uniformLocation = glGetUniformLocation(this->shaderProgram, uniformName.c_str());
    if (uniformLocation == -1)
        throw std::runtime_error("uniform named \"" + uniformName + "\" doesn't exist.");
    return uniformLocation;
}

void Shader::use() {
    glUseProgram(this->shaderProgram);
}

void Shader::updateUniform(const std::string &uniformName, float r, float g, float b, float a) {
    GLint location = this->getUniformLocation(uniformName);
    this->use();
    glUniform4f(location, r, g, b, a);
}

void Shader::updateUniform(const std::string &uniformName, glm::mat4 mat4) {
    GLint location = this->getUniformLocation(uniformName);
    this->use();
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::updateUniform(const std::string &uniformName, glm::vec3 vec3) {
    GLint location = this->getUniformLocation(uniformName);
    this->use();
    glUniform3f(location, vec3.x, vec3.y, vec3.z);
}

void Shader::updateUniform(const std::string &uniformName, float x, float y, float z) {
    GLint location = this->getUniformLocation(uniformName);
    this->use();
    glUniform3f(location, x, y, z);
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
