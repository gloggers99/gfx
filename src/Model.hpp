#pragma once

#include <string>

#include "IndicedVertexStack.hpp"

namespace GFX {

class Model {
private:
    std::string modelName;
    std::string path;

    IndicedVertexStack vertexStack;

    void loadModel();

public:
    void draw(Shader *shader);

    explicit Model(std::string path);
    ~Model();
};

}; // namespace GFX
