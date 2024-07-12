#pragma once

#include <string>
#include <thread>
#include <mutex>

#include "VertexStack.hpp"
#include "hermes/hermes.hpp"
#include "components/Material.hpp"
#include "components/Transform.hpp"

namespace GFX {

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

class Model {
private:
    Hermes::Log<char> log = Hermes::Log("GFX::Model", std::cout);

    std::string modelName;
    std::string path;

    VertexStack<Vertex> vertexStack;

    void loadModel();

public:
    Transform transform;
    Material material;

    void draw(Shader &shader);

    explicit Model(const std::string& path);
    ~Model();
};

}; // namespace GFX
