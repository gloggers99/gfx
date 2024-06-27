#include "Cube.hpp"
#include <glm/ext/matrix_transform.hpp>

namespace GFX {

void Cube::translate(float x, float y, float z) {
    this->transform = glm::translate(this->transform, glm::vec3(x, y, z));
}

void Cube::draw() {
    
}

Cube::Cube(glm::mat4 transform) : transform(transform) {
    this->vao = VAO();
    this->vbo = VBO();
    this->ebo = EBO();
}

Cube::~Cube() = default;

}; // namespace GFX
