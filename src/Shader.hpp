#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>

namespace GFX {

class Shader {
private:
    GLuint vertexShader, fragmentShader;
    GLuint shaderProgram;
    std::string vertexSource, fragmentSource;
    std::string shaderName;

    GLint getUniformLocation(const std::string &uniformName);
    void compile();
    void fetchSource();

public:
    void use();
    void recompile();
    void updateUniform(const std::string &uniformName, float r, float g, float b, float a);
    void updateUniform(const std::string &uniformName, glm::mat4 mat4);
    void updateUniform(const std::string &uniformName, glm::vec3 vec3);
    void updateUniform(const std::string &uniformName, float x, float y, float z);

    // take in a file path without extension
    explicit Shader(const std::string &shaderName);

    ~Shader();
};

}; // namespace GFX
