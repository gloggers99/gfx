#pragma once

#include "Renderer.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

namespace GFX {

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

    bool firstMouse = true;
    float yaw = -90.0f;
    float pitch = 0.0f;
    // TODO: this needs to be changed to the window size
    float lastX = 640.0f / 2.0;
    float lastY = 480.0f / 2.0;
    float fov = 90.0f;

public:
    glm::vec3 getCameraPos();

    glm::mat4 createViewMatrix();
    glm::mat4 createProjectionMatrix(Renderer *renderer);

    glm::mat4 createCameraMatrix(Renderer *renderer);

    void move(Direction direction, float speed = 2.5f);
    void handleMouse(Renderer *renderer, float sensitivity = 0.01f);

    Camera();
    ~Camera();
};

}; // namespace GFX
