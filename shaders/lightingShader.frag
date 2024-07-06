#version 330 core

layout (location = 0) out vec4 FragColor;

in vec3 FragPos;  

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    vec3 dFdxPos = dFdx(FragPos);
    vec3 dFdyPos = dFdy(FragPos);
    vec3 normal = normalize(cross(dFdxPos, dFdyPos));

    vec3 lightDir = normalize(lightPos - FragPos);
    float distanceToLight = length(lightPos - FragPos);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 lighting = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(lighting, 1.0);     
} 
