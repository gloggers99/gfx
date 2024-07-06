#include "Model.hpp"
#include "IndicedVertexStack.hpp"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

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
    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<glm::vec3> tmpVertices;
    std::vector<glm::vec2> tmpTexCoords;
    std::vector<glm::vec3> tmpNormals;

    std::vector<unsigned int> tmpIndices;
    std::vector<unsigned int> tmpTexCoordIndices;
    std::vector<unsigned int> tmpNormalIndices;

    std::ifstream file(this->path);
    if (!file.is_open())
        throw std::runtime_error("Model could not be opened.");

    std::string line;
    while (std::getline(file, line)) {
        // trim
        while (!line.empty() && isspace(line.back())) line.pop_back();

        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            tmpVertices.push_back(vertex);
        } else if (prefix == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            tmpNormals.push_back(normal);
        } else if (prefix == "vt") {
            glm::vec2 texCoord;
            ss >> texCoord.x >> texCoord.y;
            tmpTexCoords.push_back(texCoord);
        } else if (prefix == "f") {
            std::string vertexData;
            if (line.find('/') != std::string::npos) {
                for (int i = 0; i < 3; ++i) {  // Assuming triangles
                    ss >> vertexData;
                    glm::vec3 face = parseTripleFace(vertexData);

                    tmpIndices.emplace_back(face.x - 1);
                    tmpTexCoordIndices.emplace_back(face.y - 1);
                    tmpNormalIndices.emplace_back(face.z - 1);
                }
            } else {
                unsigned int x, y, z;
                ss >> x >> y >> z;
                tmpIndices.emplace_back(x - 1);
                tmpIndices.emplace_back(y - 1);
                tmpIndices.emplace_back(z - 1);
            }
        } else if (prefix == "o") {
            ss >> this->modelName;
        }
    }

    file.close();

    // utilize hashing for faster comparison of Vertex's
    struct VertexKey {
        unsigned int vertexIndex;
        unsigned int texCoordIndex;
        unsigned int normalIndex;

        bool operator==(const VertexKey &other) const {
            return vertexIndex == other.vertexIndex &&
                   texCoordIndex == other.texCoordIndex &&
                   normalIndex == other.normalIndex;
        }
    };

    struct VertexKeyHash {
        std::size_t operator()(const VertexKey &key) const {
            return ((std::hash<unsigned int>()(key.vertexIndex) ^
                     (std::hash<unsigned int>()(key.texCoordIndex) << 1)) >> 1) ^
                   (std::hash<unsigned int>()(key.normalIndex) << 1);
        }
    };

    std::unordered_map<VertexKey, unsigned int, VertexKeyHash> uniqueVertices;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < tmpIndices.size(); ++i) {
        VertexKey key{tmpIndices[i], tmpTexCoordIndices[i], tmpNormalIndices[i]};

        if (uniqueVertices.find(key) == uniqueVertices.end()) {
            Vertex vertex = {};
            vertex.position = tmpVertices[key.vertexIndex];
            vertex.texCoord = tmpTexCoords[key.texCoordIndex];
            vertex.normal = tmpNormals[key.normalIndex];

            uniqueVertices[key] = vertices.size();
            vertices.push_back(vertex);
        }

        indices.push_back(uniqueVertices[key]);
    }

    for (const Vertex &v : vertices) {
        this->vertexStack.addVertex(v);
    }
    for (unsigned int index : indices) {
        this->vertexStack.addIndex(index);
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    std::cout << "Model \'" << this->modelName <<  "\' loaded in " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms\n";
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