#include "../src/GFX.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Shader shader = GFX::Shader(
        R"(
            #version 330

            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoord;

            uniform mat4 transform;
            uniform mat4 camera;

            out vec2 TexCoord;

            void main() {
                gl_Position = camera * transform * vec4(aPos, 1.0);
                TexCoord = aTexCoord;
            }
        )",
        R"(
            #version 330

            out vec4 FragColor;
            in vec2 TexCoord;

            uniform sampler2D Texture;

            void main() {
                FragColor = texture(Texture, TexCoord);
            }
        )"
    );

    GFX::Shader lightingShader = GFX::Shader(
        R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;

            out vec3 FragPos;
            //out vec3 Normal;

            uniform mat4 transform;
            uniform mat4 camera;

            void main()
            {
                FragPos = vec3(transform * vec4(aPos, 1.0));
                //Normal = normalize(mat3(transpose(inverse(transform))) * aPos);
                
                gl_Position = camera * vec4(FragPos, 1.0);
            }
        )",
        R"(
            #version 330 core
            out vec4 FragColor;

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

                float shadowFactor = 1.0;

                vec3 rayOrigin = FragPos + 0.001 * lightDir;
                float rayLength = distanceToLight;
                vec3 rayEnd = lightPos;

                for (float t = 0.0; t < rayLength; t += 0.1) {
                    vec3 samplePoint = rayOrigin + t * lightDir;
                    if (samplePoint is inside an object) {
                        shadowFactor = 0.0; // Fragment is in shadow
                        break;
                    }
                }

                float ambientStrength = 0.1;
                vec3 ambient = ambientStrength * lightColor;

                vec3 norm = normalize(normal);
                float diff = max(dot(norm, lightDir), 0.0);
                vec3 diffuse = diff * lightColor;

                float specularStrength = 0.5;
                vec3 viewDir = normalize(viewPos - FragPos);
                vec3 reflectDir = reflect(-lightDir, norm);
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
                vec3 specular = specularStrength * spec * lightColor;

                // Final color calculation with shadow factor
                vec3 lighting = (ambient + (1.0 - shadowFactor) * (diffuse + specular)) * objectColor;
                FragColor = vec4(lighting, 1.0);     
            } 
        )"
    );

    GFX::Shader lightingCubeShader = GFX::Shader(
        R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;

            uniform mat4 transform;
            uniform mat4 camera;

            void main()
            {
                gl_Position = camera * transform * vec4(aPos, 1.0);
            }
        )",
        R"(
            #version 330 core
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(1.0); // set all 4 vector values to 1.0
            }
        )"
    );

    GFX::Camera camera = GFX::Camera();

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    renderer.hideCursor();
    
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    GFX::Cube cube1 = GFX::Cube(lightingShader);
    GFX::Cube cube2 = GFX::Cube(lightingCubeShader);

    auto draw = [&renderer, &camera, &lightingShader, &lightingCubeShader, &lightPos, &cubeVAO, &lightCubeVAO, &cube1, &cube2](int deltaTime) {
        renderer.clear();
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);

        lightingShader.updateUniform("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.updateUniform("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.updateUniform("lightPos", lightPos);
        lightingShader.updateUniform("viewPos", camera.getCameraPos());
        lightingShader.updateUniform("camera", camera.createCameraMatrix(&renderer));

        lightingCubeShader.updateUniform("camera", camera.createCameraMatrix(&renderer));
        
        cube1.draw();

        //cube2.setTransform(lightPos, glm::vec3(0.2f), glm::radians(0.0f), glm::vec3(0.0f));
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, lightPos);
        cube2.setTransform(transform);
        cube2.draw();

        /*
        glm::mat4 transform = glm::mat4(1.0f);
        lightingShader.updateUniform("transform", transform);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, lightPos);
        transform = glm::scale(transform, glm::vec3(0.2f));
        lightingCubeShader.updateUniform("camera", camera.createCameraMatrix(&renderer));
        lightingCubeShader.updateUniform("transform", transform);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        */

        renderer.swapBuffers();

        // input
        camera.handleMouse(&renderer);
        
        float cameraSpeed = 0.01 * deltaTime;

        if (renderer.getKey(GLFW_KEY_W) == GLFW_PRESS)
            camera.move(GFX::Direction::FORWARD, cameraSpeed);
        if (renderer.getKey(GLFW_KEY_S) == GLFW_PRESS)
            camera.move(GFX::Direction::BACKWARD, cameraSpeed);
        if (renderer.getKey(GLFW_KEY_A) == GLFW_PRESS)
            camera.move(GFX::Direction::LEFT, cameraSpeed);
        if (renderer.getKey(GLFW_KEY_D) == GLFW_PRESS)
            camera.move(GFX::Direction::RIGHT, cameraSpeed);
    };

    renderer.loop(draw);

    return 0;
}
