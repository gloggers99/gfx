#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include "../vo/VAO.hpp"
#include "../vo/VBO.hpp"
#include "../vo/EBO.hpp"

namespace GFX {

class Cube {
private:
    glm::mat4 transform;

    VAO vao;
    VBO vbo;
    EBO ebo;
public:
    void translate(float x, float y, float z);

    void draw();

    Cube(glm::mat4 transform);
    ~Cube();
};

}; // namespace GFX
