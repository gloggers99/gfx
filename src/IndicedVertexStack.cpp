#include "IndicedVertexStack.hpp"

#include <iostream>
#include <utility>

namespace GFX {

void IndicedVertexStack::addVertex(Vertex vertex) {
    this->vertices.push_back(vertex);
}

void IndicedVertexStack::addIndex(unsigned int index) {
    this->indices.push_back(index);
}

void IndicedVertexStack::draw(Shader *shader) {
    if (!compiled)
        this->compile();

    shader->use();
    this->vao.bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->indices.size()), GL_UNSIGNED_INT, nullptr);
    this->vao.unbind();
}

void IndicedVertexStack::compile() {
    this->vao.bind();
    this->vbo.bind();
    this->vbo.setBufferData(&this->vertices[0], this->vertices.size() * sizeof(Vertex));
    this->ebo.bind();
    this->ebo.setBufferData(&this->indices[0], this->indices.size() * sizeof(unsigned int));
    this->vbo.setAttribPointer(0, 3, sizeof(this->vertices[0]), 0);
    this->vbo.setAttribPointer(1, 2, sizeof(this->vertices[0]), 3);
    this->vbo.setAttribPointer(2, 3, sizeof(this->vertices[0]), 5);
    this->vao.unbind();

    this->compiled = true;
}

IndicedVertexStack::IndicedVertexStack() : compiled(false), vao(VAO()), vbo(VBO()), ebo(EBO()) {
    this->vertices = std::vector<Vertex>();
    this->indices = std::vector<unsigned int>();
}

IndicedVertexStack::IndicedVertexStack(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : 
    vertices(std::move(vertices)), indices(std::move(indices)), compiled(false), vao(VAO()), vbo(VBO()), ebo(EBO()) {
}

IndicedVertexStack::~IndicedVertexStack() = default;

std::ostream &operator<<(std::ostream& os, const IndicedVertexStack& stack) {
    for (Vertex v : stack.vertices) {
        os << "vertex {\n";
        os << "       position: " << v.position.x << ", " << v.position.y << ", " << v.position.z << "\n";
        os << "       texCoord: " << v.texCoord.x << ", " << v.texCoord.y << "\n";
        os << "       normal: " << v.normal.x << ", " << v.normal.y << ", " << v.normal.z << "\n";
        os << "};\n";
    }
    return os;
}

};
