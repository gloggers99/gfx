#pragma once

#include <glm/glm.hpp>

namespace GFX {

// TODO: take note of this somewhere because this
// universally will apply to all vertex shaders.
struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

}; // namespace GFX
