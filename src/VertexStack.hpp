#pragma once

#include "Shader.hpp"

#include "vo/VAO.hpp"
#include "vo/VBO.hpp"

#include "Vertex.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace GFX {

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
    explicit VertexStack(std::vector<Vertex> vertices);
    ~VertexStack();

    friend std::ostream &operator<<(std::ostream& os, const VertexStack& stack);
};

};
