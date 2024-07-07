#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 camera;
uniform mat4 transform = mat4(1.0);

void main() {
    gl_Position = camera * transform * vec4(position, 1.0);
}