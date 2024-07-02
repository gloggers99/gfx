#include "Model.hpp"
#include "IndicedVertexStack.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace GFX {

void Model::loadModel() {
    std::ifstream file(this->path);
    if (!file.is_open())
        throw std::runtime_error("Model could not be opened.");

    std::stringstream ss;

    std::string line;
    while (!file.eof()) {
        std::getline(file, line);

        ss.clear();
        ss.str(line);

        std::string token;
        float x, y, z;
        ss >> token >> x >> y >> z;
        if (token == "v") {
            this->vertexStack.addVertex({{x, y, z}});
        } if (token == "f") {
            this->vertexStack.addIndex(x - 1);
            this->vertexStack.addIndex(y - 1);
            this->vertexStack.addIndex(z - 1);
        }

            
        /*else if (line.substr(0, 2) == "vt") {
            // texture coordinates
        } else if (line.substr(0, 2) == "vn") {
            // normals
        } else if (line.substr(0, 2) == "f ") {
            // faces
        } else {
            // ignore
        }*/
    }

    file.close();
}

void Model::draw(Shader *shader) {
    this->vertexStack.draw(shader);
}

Model::Model(const std::string &path) : path(path), vertexStack(IndicedVertexStack()) {
    if (!std::filesystem::exists(this->path))
        throw std::runtime_error("Model does not exist.");

    this->loadModel();
}

Model::~Model() {
}

};
