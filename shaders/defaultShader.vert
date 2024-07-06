#version 330

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;

uniform mat4 transform = mat4(1.0);
uniform mat4 camera;

out vec3 Normal;

void main() {
    //gl_Position = camera * transform * vec4(position, 1.0);
    gl_Position = camera * transform * vec4(position, 1.0);
    Normal = mat3(transpose(inverse(transform))) * normal;
}
