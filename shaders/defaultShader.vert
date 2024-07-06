#version 330

layout (location = 0) in vec3 position;

uniform mat4 transform = mat4(1.0);
uniform mat4 camera;

void main() {
    //gl_Position = camera * transform * vec4(position, 1.0);
    gl_Position = camera * transform * vec4(position, 1.0);
}
