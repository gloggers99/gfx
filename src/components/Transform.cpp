#include <stdexcept>
#include "Transform.hpp"
#include "../Shader.hpp"

namespace GFX {

glm::mat4 Transform::getTransform() {
    return this->transform;
}

MatrixComponents Transform::decompose() {
    MatrixComponents components;

    glm::decompose(this->transform,
                   components.scale,
                   components.rotation,
                   components.translation,
                   components.skew,
                   components.perspective);

    return components;
}

void Transform::compose(MatrixComponents components) {
    this->transform = glm::recompose(components.scale,
                                     components.rotation,
                                     components.translation,
                                     components.skew,
                                     components.perspective);
}

glm::vec3 Transform::getTranslation() {
    return this->decompose().translation;
}

glm::vec3 Transform::getScale() {
    return this->decompose().scale;
}

glm::quat Transform::getRotation() {
    return this->decompose().rotation;
}

void Transform::translate(glm::vec3 translation) {
    this->transform = glm::translate(this->transform, translation);
}

void Transform::scale(glm::vec3 scale) {
    this->transform = glm::scale(this->transform, scale);
}

void Transform::rotate(float angle, glm::vec3 axis) {
    this->transform = glm::rotate(this->transform, glm::radians(angle), axis);
}

void Transform::setTranslation(glm::vec3 translation) {
    MatrixComponents components = this->decompose();
    components.translation = translation;
    this->compose(components);
}

void Transform::setScale(glm::vec3 scale) {
    MatrixComponents components = this->decompose();
    components.scale = scale;
    this->compose(components);
}

void Transform::setRotation(glm::quat rotation) {
    MatrixComponents components = this->decompose();
    components.rotation = rotation;
    this->compose(components);
}

void Transform::reset() {
    this->transform = glm::mat4(1.0f);
}

void Transform::apply() {
    this->fairingData->updateUniform("transform", this->transform);
}

void Transform::unapply() {
    this->fairingData->updateUniform("transform", glm::mat4(1.0f));
}

Transform::Transform() : transform(glm::mat4(1.0f)) {}

Transform::~Transform() = default;

} // namespace GFX