#version 330

layout (location = 0) out vec4 FragColor;

in vec3 Normal;

void main() {
    // Normalize the normal vector to ensure it has a length of 1
    vec3 normalizedNormal = normalize(Normal);

    // Determine the major axis of the normal vector
    vec3 absNormal = abs(normalizedNormal);
    vec3 color = vec3(0.0);

    if (absNormal.x > absNormal.y && absNormal.x > absNormal.z) {
        color = (normalizedNormal.x > 0.0) ? vec3(1.0, 0.0, 0.0) : vec3(0.5, 0.0, 0.0); // Red for +x, dark red for -x
    } else if (absNormal.y > absNormal.x && absNormal.y > absNormal.z) {
        color = (normalizedNormal.y > 0.0) ? vec3(0.0, 1.0, 0.0) : vec3(0.0, 0.5, 0.0); // Green for +y, dark green for -y
    } else {
        color = (normalizedNormal.z > 0.0) ? vec3(0.0, 0.0, 1.0) : vec3(0.0, 0.0, 0.5); // Blue for +z, dark blue for -z
    }

    FragColor = vec4(color, 1.0);
}
