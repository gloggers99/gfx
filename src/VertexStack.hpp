#pragma once

#include "Shader.hpp"

#include "vo/VAO.hpp"
#include "vo/VBO.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace GFX {

// TODO: take note of this somewhere because this
// universally will apply to all vertex shaders.
struct Vertex {
    glm::vec3 position;
};

class VertexStack {
private:
    std::vector<Vertex> vertices;

    VAO vao;
    VBO vbo;

    bool compiled;

public:
    void add(Vertex vertex);
    void draw(Shader *shader);
    void compile();

    VertexStack();
    VertexStack(std::vector<Vertex> vertices);
    ~VertexStack();

    friend VertexStack operator+(VertexStack &lhs, VertexStack &rhs);
};

};
