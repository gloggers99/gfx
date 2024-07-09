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

glm::mat4 Camera::createProjectionMatrix(Renderer *renderer) const {
    int width, height;
    renderer->getSize(&width, &height);

    return glm::perspective(glm::radians(this->fov), (float)width / (float)height, 0.1f, 100.0f);
}

glm::mat4 Camera::createCameraMatrix(Renderer *renderer) {
    return this->createProjectionMatrix(renderer) * this->createViewMatrix();
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

void Camera::handleMouse(Renderer &renderer, float sensitivity) {
    double xpos, ypos;
    renderer.getCursorPos(&xpos, &ypos);

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
    cameraPos(glm::vec3(0.0f, 0.0f, 0.0f)),
    cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    fov(fov),
    firstMouse(true),
    yaw(-90.0f),
    pitch(0.0f) {
    int w, h;
    renderer.getSize(&w, &h);

    this->lastX = static_cast<float>(w) / 2.0f;
    this->lastY = static_cast<float>(h) / 2.0f;
}

Camera::~Camera() = default;

}; // namespace GFX
