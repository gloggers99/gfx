#pragma once

#include <string>
#include <thread>
#include <mutex>

#include "VertexStack.hpp"
#include "hermes/hermes.hpp"

namespace GFX {

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

class Model {
private:
    Hermes::Log<char> log = Hermes::Log("GFX::Model", std::cout);

    std::thread importThread;
    std::mutex importThreadLock;

    std::string modelName;
    std::string path;

    VertexStack<Vertex> vertexStack;
    bool loaded;

    void loadModel();

public:
    bool isLoaded();
    void draw(Shader *shader);

    explicit Model(std::string path);
    ~Model();
};

}; // namespace GFX
