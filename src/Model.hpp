#pragma once

#include <string>
#include <thread>
#include <mutex>

#include "IndicedVertexStack.hpp"

namespace GFX {

class Model {
private:
    std::thread importThread;
    std::mutex importThreadLock;

    std::string modelName;
    std::string path;

    IndicedVertexStack vertexStack;
    bool loaded;

    void loadModel();

public:
    void draw(Shader *shader);

    explicit Model(std::string path);
    ~Model();
};

}; // namespace GFX
