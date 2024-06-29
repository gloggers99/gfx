#include "Shader.hpp"

#include <filesystem>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace GFX {

GLint Shader::getUniformLocation(const std::string &uniformName) {
    GLint uniformLocation = glGetUniformLocation(this->shaderProgram, uniformName.c_str());
    if (uniformLocation == -1)
        throw std::runtime_error("uniform named \"" + uniformName + "\" doesn't exist.");
    return uniformLocation;
}

bool Shader::compile() {
    int success;
    char buffer[512];

    // vertex shader
    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexSource = this->vertexSource.c_str();
    glShaderSource(this->vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(this->vertexShader);
    glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(this->vertexShader, 512, nullptr, buffer);
        std::cerr << "\nVertex shader failed to compile:\n\n" << buffer << "\n";
        return false;
    }

    // fragment shader
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentSource = this->fragmentSource.c_str();
    glShaderSource(this->fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(this->fragmentShader);
    glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(this->fragmentShader, 512, nullptr, buffer);
        std::cerr << "\nFragment shader failed to compile:\n\n" << buffer << "\n";
        return false;
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
        return false;
    }

    return true;
}

void Shader::fetchSource() {
    if (!std::filesystem::exists("shaders/" + shaderName + ".vert"))
        throw std::runtime_error("vertex shader file doesn't exist.");

    if (!std::filesystem::exists("shaders/" + shaderName + ".frag"))
        throw std::runtime_error("fragment shader file doesn't exist.");

    std::ifstream vertexFile("shaders/" + shaderName + ".vert");
    std::stringstream vertexStream;
    vertexStream << vertexFile.rdbuf();
    this->vertexSource = vertexStream.str();

    std::ifstream fragmentFile("shaders/" + shaderName + ".frag");
    std::stringstream fragmentStream;
    fragmentStream << fragmentFile.rdbuf();
    this->fragmentSource = fragmentStream.str();
}

void Shader::use() {
    glUseProgram(this->shaderProgram);
}

bool Shader::recompile() {
    GLint oldProgram = this->shaderProgram;
    glUseProgram(0);
    this->fetchSource();
    if (!this->compile()) {
        this->shaderProgram = oldProgram;
        std::cerr << "Shader recompilation failed.\n";
    } else {
        glDeleteProgram(oldProgram);
        std::cerr << "Shader recompiled successfully.\n";
    }
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

Shader::Shader(const std::string &shaderName) : shaderName(shaderName) {
    this->fetchSource();
    this->compile();
}

Shader::~Shader() {
    glDeleteProgram(this->shaderProgram);
}

}; // namespace GFX
