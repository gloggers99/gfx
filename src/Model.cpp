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
#include <iostream>

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
    std::vector<glm::vec2> tmpTexCoords;
    std::vector<glm::vec3> tmpNormals;

    // indices
    std::vector<unsigned int> tmpIndices;
    std::vector<unsigned int> tmpTexCoordIndices;
    std::vector<unsigned int> tmpNormalIndices;

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
        } else if (line.substr(0, 2) == "vn") {
            std::string token;
            int x, y, z;

            ss >> token >> x >> y >> z;
            tmpNormals.emplace_back(x, y, z);
        } else if (line.substr(0, 2) == "vt") {
            std::string token;
            int x, y;

            ss >> token >> x >> y;
            tmpTexCoords.emplace_back(x, y);
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
                tmpIndices.emplace_back(xFace.x - 1);
                tmpTexCoordIndices.emplace_back(xFace.y);
                tmpNormalIndices.emplace_back(xFace.z);

                glm::vec3 yFace = parseTripleFace(y);
                tmpIndices.emplace_back(yFace.x - 1);
                tmpTexCoordIndices.emplace_back(yFace.y);
                tmpNormalIndices.emplace_back(yFace.z);

                glm::vec3 zFace = parseTripleFace(z);
                tmpIndices.emplace_back(zFace.x - 1);
                tmpTexCoordIndices.emplace_back(zFace.y);
                tmpNormalIndices.emplace_back(zFace.z);

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

    std::vector<Vertex> vertices;

    for (glm::vec3 normals : tmpNormals) {
        std::cout << "normal: " << normals.x << ", " << normals.y << ", " << normals.z << "\n";
    }

    for (size_t i = 0; i < tmpVertices.size(); i++) {

        vertices.emplace_back(Vertex {
            tmpVertices[i],
            tmpTexCoords[tmpTexCoordIndices[i * 3]],
            tmpNormals[tmpNormalIndices[i * 3]]
        });
    }

    for (Vertex &v : vertices) {
        this->vertexStack.addVertex(v);
    }
    for (unsigned int tmpIndice : tmpIndices) {
        this->vertexStack.addIndex(tmpIndice);
    }

}

void Model::draw(Shader *shader) {
    this->vertexStack.draw(shader);
}

Model::Model(std::string path) : path(std::move(path)), vertexStack(IndicedVertexStack()) {
    if (!std::filesystem::exists(this->path))
        throw std::runtime_error("Model does not exist.");

    this->loadModel();

    std::cout << this->vertexStack << "\n";
}

Model::~Model() {
}

}; // namespace GFX