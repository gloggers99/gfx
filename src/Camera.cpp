#include "Camera.hpp"
#include "Renderer.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <stdexcept>

namespace GFX {

glm::vec3 Camera::getCameraPos() {
    return this->cameraPos;
}

glm::mat4 Camera::createViewMatrix() {
    return glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);
}

glm::mat4 Camera::createProjectionMatrix() const {
    auto size = this->renderer.getSize();

    return glm::perspective(glm::radians(this->fov), (float)size.first / (float)size.second, 0.1f, 100.0f);
}

glm::mat4 Camera::createCameraMatrix() {
    return this->createProjectionMatrix() * this->createViewMatrix();
}

void Camera::move(Direction direction, float speed) {
    switch (direction) {
        case Direction::FORWARD:
            this->cameraPos += cameraFront * speed;
            break;
        case Direction::BACKWARD:
            this->cameraPos -= cameraFront * speed;
            break;
        case Direction::LEFT:
            this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * speed;
            break;
        case Direction::RIGHT:
            this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * speed;
            break;
        default:
            throw std::runtime_error("invalid direction provided.");
    }
}

void Camera::handleMouse(float sensitivity) {
    auto pos = this->renderer.getCursorPos();
    double xpos = pos.first;
    double ypos = pos.second;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front.y = std::sin(glm::radians(pitch));
    front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

Camera::Camera(Renderer &renderer, float fov) :
    renderer(renderer),
    cameraPos(glm::vec3(0.0f, 0.0f, 0.0f)),
    cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    fov(fov),
    firstMouse(true),
    yaw(-90.0f),
    pitch(0.0f) {
    auto size = this->renderer.getSize();

    this->lastX = static_cast<float>(size.first) / 2.0f;
    this->lastY = static_cast<float>(size.second) / 2.0f;
}

Camera::~Camera() = default;

}; // namespace GFX
