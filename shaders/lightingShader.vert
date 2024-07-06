#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 FragPos;

uniform mat4 transform;
uniform mat4 camera;

void main()
{
    FragPos = vec3(transform * vec4(aPos, 1.0));
    
    gl_Position = camera * vec4(FragPos, 1.0);
}
