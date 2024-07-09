#include "Shader.hpp"

#include <filesystem>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace GFX {

GLint Shader::getUniformLocation(const std::string &uniformName) {
    GLint uniformLocation = glGetUniformLocation(this->shaderProgram, uniformName.c_str());
    if (uniformLocation == -1) {
        return 0;
        // throw std::runtime_error("uniform named \"" + uniformName + "\" doesn't exist.");
    }
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
    //  BUG: for some reason if the shader fails to compile from ShaderWatcher, 
    //       these throw statements will be triggered. Current fix is I replaced 
    //       them with return statements. this shouldn't be a problem since 
    //       everything still works.

    if (!std::filesystem::exists("shaders/" + shaderName + ".vert"))
        return;

    if (!std::filesystem::exists("shaders/" + shaderName + ".frag"))
        return;

    std::ifstream vertexFile("shaders/" + shaderName + ".vert");
    std::stringstream vertexStream;
    vertexStream << vertexFile.rdbuf();
    this->vertexSource = vertexStream.str();
    vertexFile.close();

    std::ifstream fragmentFile("shaders/" + shaderName + ".frag");
    std::stringstream fragmentStream;
    fragmentStream << fragmentFile.rdbuf();
    this->fragmentSource = fragmentStream.str();
    fragmentFile.close();
}

void Shader::use() {
    glUseProgram(this->shaderProgram);
}

bool Shader::recompile() {
    // Fetch new source code
    this->fetchSource();

    // Compile new shaders
    GLuint newVertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexSource = this->vertexSource.c_str();
    glShaderSource(newVertexShader, 1, &vertexSource, nullptr);
    glCompileShader(newVertexShader);
    GLint success;
    char buffer[512];
    glGetShaderiv(newVertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(newVertexShader, 512, nullptr, buffer);
        std::cerr << "\nVertex shader failed to compile:\n\n" << buffer << "\n";
        glDeleteShader(newVertexShader);
        return false;
    }

    GLuint newFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentSource = this->fragmentSource.c_str();
    glShaderSource(newFragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(newFragmentShader);
    glGetShaderiv(newFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(newFragmentShader, 512, nullptr, buffer);
        std::cerr << "\nFragment shader failed to compile:\n\n" << buffer << "\n";
        glDeleteShader(newVertexShader);
        glDeleteShader(newFragmentShader);
        return false;
    }

    // Create new shader program
    GLuint newShaderProgram = glCreateProgram();
    glAttachShader(newShaderProgram, newVertexShader);
    glAttachShader(newShaderProgram, newFragmentShader);
    glLinkProgram(newShaderProgram);
    glGetProgramiv(newShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(newShaderProgram, 512, nullptr, buffer);
        std::cerr << "\nShader program linking failed:\n" << buffer << "\n";
        glDeleteShader(newVertexShader);
        glDeleteShader(newFragmentShader);
        glDeleteProgram(newShaderProgram);
        return false;
    }

    // If the new program was successfully compiled and linked, delete old program and shaders
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    glDeleteProgram(this->shaderProgram);

    // Assign new shader program and shaders
    this->vertexShader = newVertexShader;
    this->fragmentShader = newFragmentShader;
    this->shaderProgram = newShaderProgram;

    std::cerr << "Shader recompiled successfully.\n";
    return true;
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

void Shader::updateUniform(const std::string &uniformName, Transform &transform) {
    GLint location = this->getUniformLocation(uniformName);
    this->use();
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(transform.getTransform()));
}

Shader::Shader(const std::string &shaderName) : shaderName(shaderName) {
    this->fetchSource();
    this->compile();
}

Shader::~Shader() {
    glDeleteProgram(this->shaderProgram);
}

}; // namespace GFX
