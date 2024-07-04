#pragma once

#include "Vertex.hpp"

#include "vo/VAO.hpp"
#include "vo/VBO.hpp"
#include "vo/EBO.hpp"

#include "Shader.hpp"

#include <vector>

namespace GFX {

class IndicedVertexStack {
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    VAO vao;
    VBO vbo;
    EBO ebo;

    bool compiled;

public:
    void addVertex(Vertex vertex);
    void addIndex(unsigned int index);

    void draw(Shader *shader);
    void compile();

    IndicedVertexStack();
    IndicedVertexStack(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~IndicedVertexStack();

    friend std::ostream &operator<<(std::ostream& os, const IndicedVertexStack& stack);
};

}; // namespace GFX
