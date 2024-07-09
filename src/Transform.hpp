#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace GFX {

typedef struct {
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
} MatrixComponents;

class Transform {
private:
    glm::mat4 transform;

public:
    glm::mat4 getTransform();

    MatrixComponents decompose();
    void compose(MatrixComponents);

    glm::vec3 getTranslation();
    glm::vec3 getScale();
    glm::quat getRotation();

    void translate(glm::vec3 translation);
    void scale(glm::vec3 scale);
    void rotate(float angle, glm::vec3 axis);

    void setTranslation(glm::vec3 translation);
    void setScale(glm::vec3 scale);
    void setRotation(glm::quat rotation);

    void reset();

    Transform();
    ~Transform();
};

} // namespace GFX
