#include "VertexStack.hpp"

namespace GFX {

void VertexStack::add(Vertex vertex) {
    this->vertices.push_back(vertex);
}

void VertexStack::draw(Shader *shader) {
    if (!compiled)
        this->compile();

    shader->use();
    this->vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
    this->vao.unbind();
}

// INFO: im PRETTY confident that this will be able to 
//       compile over and over again using new data, I 
//       want to avoid using dynamic draw for now.
void VertexStack::compile() {
    this->vao.bind();
    this->vbo.bind();
    this->vbo.setBufferData(&this->vertices[0], this->vertices.size() * sizeof(Vertex));
    this->vbo.setAttribPointer(0, 3, sizeof(this->vertices[0]), 0);
    this->vao.unbind();

    this->compiled = true;
}

VertexStack::VertexStack() {
    this->vertices = std::vector<Vertex>();
}

VertexStack::VertexStack(std::vector<Vertex> vertices) : vertices(vertices), compiled(false) {
}

VertexStack::~VertexStack() {
}

VertexStack operator+(VertexStack &lhs, VertexStack &rhs) {
    VertexStack newStack = VertexStack(lhs.vertices);
    for (Vertex vertex : rhs.vertices) {
        newStack.add(vertex);
    }
    return newStack;
}

}; // namespace GFX
