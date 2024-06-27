#include "Cube.hpp"
#include <GL/gl.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

namespace GFX {

void Cube::draw() {
    this->vao.bind();
    this->shader.use();

    // draw front
    this->frontTexture->bind();
    this->shader.updateUniform("transform", this->transform);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    this->shader.updateUniform("transform", glm::mat4(1.0f));
    
    // draw back
    this->backTexture->bind();
    this->shader.updateUniform("transform", this->transform * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    this->shader.updateUniform("transform", glm::mat4(1.0f));

    // draw left
    this->leftTexture->bind();
    this->shader.updateUniform("transform", 
            this->transform 
            * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    this->shader.updateUniform("transform", glm::mat4(1.0f));

    // draw right
    this->rightTexture->bind();
    this->shader.updateUniform("transform", 
            this->transform 
            * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    this->shader.updateUniform("transform", glm::mat4(1.0f));

    // draw top
    this->topTexture->bind();
    this->shader.updateUniform("transform", 
            this->transform 
            * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    this->shader.updateUniform("transform", glm::mat4(1.0f));

    // draw bottom
    this->bottomTexture->bind();
    this->shader.updateUniform("transform", 
            this->transform 
            * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    this->shader.updateUniform("transform", glm::mat4(1.0f));
    glBindTexture(GL_TEXTURE_2D, 0);

    this->vao.unbind();
}

void Cube::translate(glm::vec3 translation) {
    this->transform = glm::translate(this->transform, translation);
}

void Cube::scale(glm::vec3 scale) {
    this->transform = glm::scale(this->transform, scale);
}

void Cube::setTexture(Texture *texture) {
    this->topTexture = texture;
    this->bottomTexture = texture;
    this->frontTexture = texture;
    this->backTexture = texture;
    this->leftTexture = texture;
    this->rightTexture = texture;
}

void Cube::setTexture(Texture *texture, Face face) {
    switch (face) {
        case Face::TOP:
            this->topTexture = texture;
            break;
        case Face::BOTTOM:
            this->bottomTexture = texture;
            break;
        case Face::FRONT:
            this->frontTexture = texture;
            break;
        case Face::BACK:
            this->backTexture = texture;
            break;
        case Face::LEFT:
            this->leftTexture = texture;
            break;
        case Face::RIGHT:
            this->rightTexture = texture;
            break;
    }
}

void Cube::setTexture(std::map<Texture*, Face> textures) {
    for (auto &texture : textures) {
        this->setTexture(texture.first, texture.second);
    }
}

Cube::Cube(Shader &shader) 
    : shader(shader),
    topTexture(new Texture("img/missing.jpeg")),
    bottomTexture(new Texture("img/missing.jpeg")),
    frontTexture(new Texture("img/missing.jpeg")),
    backTexture(new Texture("img/missing.jpeg")),
    leftTexture(new Texture("img/missing.jpeg")),
    rightTexture(new Texture("img/missing.jpeg")),
    vao(VAO()),
    vbo(VBO()), 
    ebo(EBO()) {
        // INFO: this MIGHT be the wrong approach, however instead of
        //       putting every vertice in one array, we can use one EBO
        //       and draw each side individually, this way we can have
        //       seperate textures for each side, and i can use GLM to modify 
        //       the vertices in the future.

        float cubeVertices[] = {
            0.5f,  0.5f, -0.5f,    0.5f, 0.5f,
            0.5f, -0.5f, -0.5f,    0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,   -0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,   -0.5f, 0.5f
        };
        unsigned int cubeIndices[] = { 
            0, 1, 3,
            1, 2, 3,
        };

        this->vao.bind();

        this->vbo.bind();
        this->vbo.setBufferData(cubeVertices, sizeof(cubeVertices));
        this->vbo.setAttribPointer(0, 3, 5 * sizeof(float), 0);
        this->vbo.setAttribPointer(1, 2, 5 * sizeof(float), 3);

        this->ebo.bind();
        this->ebo.setBufferData(cubeIndices, sizeof(cubeIndices));

        this->vao.unbind();
    }

Cube::~Cube() {
}

}; // namespace GFX
