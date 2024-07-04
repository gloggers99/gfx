#include "IndicedVertexStack.hpp"

#include <iostream>

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
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    this->vao.unbind();
}

void IndicedVertexStack::compile() {
    this->vao.bind();
    this->vbo.bind();
    this->vbo.setBufferData(&this->vertices[0], this->vertices.size() * sizeof(Vertex));
    this->ebo.bind();
    this->ebo.setBufferData(&this->indices[0], this->indices.size() * sizeof(unsigned int));
    this->vbo.setAttribPointer(0, 3, sizeof(this->vertices[0]), 0);
    this->vao.unbind();

    this->compiled = true;
}

IndicedVertexStack::IndicedVertexStack() : compiled(false), vao(VAO()), vbo(VBO()), ebo(EBO()) {
    this->vertices = std::vector<Vertex>();
    this->indices = std::vector<unsigned int>();
}

IndicedVertexStack::IndicedVertexStack(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : 
    vertices(vertices), indices(indices), compiled(false), vao(VAO()), vbo(VBO()), ebo(EBO()) {
}

IndicedVertexStack::~IndicedVertexStack() {
}

std::ostream &operator<<(std::ostream& os, const IndicedVertexStack& stack) {
    os << "IndicedVertexStack {\n";
    os << "    vertices: " << stack.vertices.size() << " vertices\n";
    os << "    indices: " << stack.indices.size() << " indices\n";
    os << "    compiled: " << stack.compiled << "\n";
    os << "}";
    return os;
}

};
