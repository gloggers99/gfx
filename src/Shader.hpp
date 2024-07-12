#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include "Camera.hpp"

class ShaderWatcher;

namespace GFX {

class Shader {
private:
    GLuint vertexShader, fragmentShader;
    GLuint shaderProgram;
    std::string vertexSource, fragmentSource;
    std::string shaderName;

    GLint getUniformLocation(const std::string &uniformName);
    bool compile();
    void fetchSource();

public:
    void use();
    bool recompile();
    void updateUniform(const std::string &uniformName, float r, float g, float b, float a);
    void updateUniform(const std::string &uniformName, glm::mat4 mat4);
    void updateUniform(const std::string &uniformName, glm::vec3 vec3);
    void updateUniform(const std::string &uniformName, float x, float y, float z);
    void updateUniform(const std::string &uniformName, GLint i);

    // take in a file path without extension
    explicit Shader(std::string shaderName);

    ~Shader();

    friend class ShaderWatcher;
};

}; // namespace GFX
