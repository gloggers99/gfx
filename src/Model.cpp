#include "Model.hpp"
#include "IndicedVertexStack.hpp"

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace GFX {

glm::vec3 parseTripleFace(const std::string& face) {
    std::stringstream ss(face);
    std::string x, y, z;
    getline(ss, x, '/');
    getline(ss, y, '/');
    getline(ss, z, '/');

    unsigned int xi = 0;
    unsigned int yi = 0;
    unsigned int zi = 0;

    try {
        xi = std::stoi(x);
    } catch (std::exception &e) {}

    try {
        yi = std::stoi(y);
    } catch (std::exception &e) {}

    try {
        zi = std::stoi(z);
    } catch (std::exception &e) {}

    return {
            xi,
            yi,
            zi
    };
}

void Model::loadModel() {
    // we must first load them into here so we can assemble them together in the end.
    std::vector<glm::vec3> tmpVertices;

    std::vector<unsigned int> tmpIndices;
    std::vector<unsigned int> tmpTexCoords;
    std::vector<unsigned int> tmpNormals;

    std::ifstream file(this->path);
    if (!file.is_open())
        throw std::runtime_error("Model could not be opened.");

    std::stringstream ss;
    std::string line;
    while (!file.eof()) {
        std::getline(file, line);

        // trim
        while ( !line.empty() && isspace(line.back()) ) line.pop_back();
        ss.clear();
        ss.str(line);

        if (line.substr(0, 2) == "v ") {
            char token;
            float x, y, z;

            ss >> token >> x >> y >> z;
            tmpVertices.emplace_back(x, y, z);
        } else if (line.substr(0, 1) == "f") {
            if (line.find('/') != std::string::npos) {
                // the format of the face is "f vertex/texCoord/normal * 4" OR * 3 in this case.
                // this is just ridiculous

                // count space:
                int count = std::count(line.begin(), line.end(), ' ');
                if (count == 4)
                    throw std::runtime_error("Model face is a quad. Please load a triangulated model.");
                // TODO: Convert quad OBJ files to triangulated OBJ files.

                // it seems in this format of the OBJ file the faces are zero-indexed.
                char token;
                std::string x, y, z;
                ss >> token >> x >> y >> z;

                glm::vec3 xFace = parseTripleFace(x);
                tmpIndices.push_back(xFace.x);
                //tmpTexCoords.push_back(xFace.y);
                //tmpNormals.push_back(xFace.z);

                glm::vec3 yFace = parseTripleFace(y);
                tmpIndices.push_back(yFace.x);
                //tmpTexCoords.push_back(yFace.y);
                //tmpNormals.push_back(yFace.z);

                glm::vec3 zFace = parseTripleFace(z);
                tmpIndices.push_back(zFace.x);
                //tmpTexCoords.push_back(zFace.y);
                //tmpNormals.push_back(zFace.z);

            } else {
                // the format of the face is "f x y z" in this case.
                char token;
                unsigned int x, y, z;
                ss >> token >> x >> y >> z;

                this->vertexStack.addIndex(x - 1);
                this->vertexStack.addIndex(y - 1);
                this->vertexStack.addIndex(z - 1);
            }

        } else {
        }
    }

    file.close();

    for (size_t i = 0; i < tmpVertices.size(); i++) {
        this->vertexStack.addVertex({tmpVertices[i]});
    }
    for (size_t i = 0; i < tmpIndices.size(); i++) {
        this->vertexStack.addIndex(tmpIndices[i]);
    }

}

void Model::draw(Shader *shader) {
    this->vertexStack.draw(shader);
}

Model::Model(std::string path) : path(std::move(path)), vertexStack(IndicedVertexStack()) {
    if (!std::filesystem::exists(this->path))
        throw std::runtime_error("Model does not exist.");

    this->loadModel();
}

Model::~Model() {
}

}; // namespace GFX