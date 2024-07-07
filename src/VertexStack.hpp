#pragma once

#include "Shader.hpp"

#include "vo/VAO.hpp"
#include "vo/VBO.hpp"
#include "vo/EBO.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace GFX {

template<typename T>
class VertexStack {
private:
    std::vector<T> vertices;
    std::vector<unsigned int> indices;
    std::vector<unsigned int> vertexTable;

    VAO vao;
    VBO vbo;
    EBO ebo;

    bool compiled;

public:
    VAO getVAO() {return this->vao;}
    void addVertex(T vertex) {
        this->vertices.emplace_back(vertex);
        if (compiled)
            this->compiled = false;
    }

    void addIndex(unsigned int index) {
        this->indices.emplace_back(index);
        if (compiled)
            this->compiled = false;
    }

    void draw(Shader *shader) {
        if (!compiled)
            this->compile();

        shader->use();
        this->vao.bind();
        if (indices.empty())
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(this->vertices.size()));
        else
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->indices.size()), GL_UNSIGNED_INT, nullptr);
        this->vao.unbind();
    }

    // INFO: im PRETTY confident that this will be able to
    //       compile over and over again using new data, I
    //       want to avoid using dynamic draw for now.
    void compile() {
        this->vao.bind();
        this->vbo.bind();
        this->vbo.setBufferData(&this->vertices[0], this->vertices.size() * sizeof(T));
        if (!indices.empty()) {
            this->ebo.bind();
            this->ebo.setBufferData(&this->indices[0], this->indices.size() * sizeof(unsigned int));
        }
        unsigned int offset = 0;
        for (size_t i = 0; i < this->vertexTable.size(); i++) {
            this->vbo.setAttribPointer(i, this->vertexTable[i], sizeof(this->vertices[0]), offset);
            offset += this->vertexTable[i];
        }
        this->vao.unbind();

        this->compiled = true;
    }

    // this is BS but apparently templated functions
    // dont get linked into the program which is just ridiculous,
    // so we must define it in the header
    VertexStack(std::vector<T> vertices, std::vector<unsigned int> vertexTable) :
            vertices(std::move(vertices)),
            vertexTable(std::move(vertexTable)),
            vao(VAO()), vbo(VBO()), ebo(EBO()),
            compiled(false) {}
    explicit VertexStack(std::vector<unsigned int> vertexTable) : vertexTable(std::move(vertexTable)), vao(VAO()), vbo(VBO()), ebo(EBO()), compiled(false) {}
    //VertexStack(std::vector<T> vertices, std::vector<unsigned int> vertexTable);
    ~VertexStack() = default;
};

};
