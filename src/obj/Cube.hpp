#pragma once

#include <glm/fwd.hpp>
#include <map>

#include "../Shader.hpp"

#include "../Texture.hpp"

#include "../vo/VAO.hpp"
#include "../vo/VBO.hpp"
#include "../vo/EBO.hpp"

namespace GFX {

enum class Face {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

class Cube {
private:
    glm::mat4 transform = glm::mat4(1.0f);
    // in the future we need a global shader program generator
    Shader &shader;

    Texture *topTexture;
    Texture *bottomTexture;
    Texture *frontTexture;
    Texture *backTexture;
    Texture *leftTexture;
    Texture *rightTexture;

    // i feel like we can abstract gpu objects more
    VAO vao;
    VBO vbo;
    EBO ebo;

public:
    void draw();

    void translate(glm::vec3 translation);
    void scale(glm::vec3 scale);

    void setTexture(Texture *texture); // set all sides to the same texture
    void setTexture(Texture *texture, Face face); // set a specific side to a texture
    void setTexture(std::map<Texture*, Face> textures); // set multiple sides to different textures

    Cube(Shader &shader);
    ~Cube();
};

}; // namespace GFX
