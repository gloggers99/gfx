#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

namespace GFX {

class Renderer;

enum class Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float fov;

    bool firstMouse;
    float yaw;
    float pitch;

    float lastX;
    float lastY;

public:
    glm::vec3 getCameraPos();

    glm::mat4 createViewMatrix();
    glm::mat4 createProjectionMatrix(Renderer *renderer) const;

    glm::mat4 createCameraMatrix(Renderer *renderer);

    void move(Direction direction, float speed = 2.5f);
    void handleMouse(Renderer &renderer, float sensitivity = 0.5f);

    explicit Camera(Renderer &renderer, float fov = 90.0f);
    ~Camera();
};

}; // namespace GFX
