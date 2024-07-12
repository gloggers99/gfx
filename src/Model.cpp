#include "Model.hpp"
#include "VertexStack.hpp"

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
    glm::vec3 result(0, 0, 0);  // Initialize to zeros
    size_t firstSlash = face.find('/');
    size_t secondSlash = face.find('/', firstSlash + 1);

    if (firstSlash != std::string::npos) {
        // Parse vertex index
        if (firstSlash > 0) {
            result.x = std::strtol(face.c_str(), nullptr, 10);
        }

        // Parse texture coordinate index
        if (secondSlash != std::string::npos) {
            if (secondSlash > firstSlash + 1) {
                result.y = std::strtol(face.c_str() + firstSlash + 1, nullptr, 10);
            } else {
                result.y = -1;  // Indicate that the texture coordinate is missing
            }
            // Parse normal index
            if (secondSlash < face.size() - 1) {
                result.z = std::strtol(face.c_str() + secondSlash + 1, nullptr, 10);
            } else {
                result.z = -1;  // Indicate that the normal is missing
            }
        } else {
            // If there's only one slash, it means the format is v/t
            result.y = std::strtol(face.c_str() + firstSlash + 1, nullptr, 10);
            result.z = -1;  // Indicate that the normal is missing
        }
    } else {
        // Only vertex index is present
        result.x = std::strtol(face.c_str(), nullptr, 10);
    }

    return result;
}

void Model::loadModel() {
    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<glm::vec3> tmpVertices;
    std::vector<glm::vec2> tmpTexCoords;
    std::vector<glm::vec3> tmpNormals;

    std::vector<unsigned int> tmpIndices;
    std::vector<int> tmpTexCoordIndices;
    std::vector<int> tmpNormalIndices;

    // load whole file into a buffer
    std::ifstream file(this->path);
    if (!file.is_open())
        throw std::runtime_error("Model could not be opened.");

    std::string buffer;
    std::stringstream fileDumper;
    fileDumper << file.rdbuf();
    buffer = fileDumper.str();

    file.close();

    std::stringstream bufferStream(buffer);

    std::string line;
    while (std::getline(bufferStream, line)) {
        // trim
        //while (!line.empty() && isspace(line.back())) line.pop_back();

        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            tmpVertices.emplace_back(vertex);
        } else if (prefix == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            tmpNormals.emplace_back(normal);
        } else if (prefix == "vt") {
            glm::vec2 texCoord;
            ss >> texCoord.x >> texCoord.y;
            tmpTexCoords.emplace_back(texCoord);
        } else if (prefix == "f") {
            std::string vertexData;
            if (line.find('/') != std::string::npos) {
                if (std::count(line.begin(), line.end(), ' ') == 3) {
                    for (int i = 0; i < 3; ++i) {
                        ss >> vertexData;
                        glm::vec3 face = parseTripleFace(vertexData);

                        tmpIndices.emplace_back(face.x - 1);
                        tmpTexCoordIndices.emplace_back(face.y - 1);
                        tmpNormalIndices.emplace_back(face.z - 1);
                    }
                } else {
                    std::string face1, face2, face3, face4;
                    ss >> face1 >> face2 >> face3 >> face4;

                    glm::vec3 faceA = parseTripleFace(face1);
                    glm::vec3 faceB = parseTripleFace(face2);
                    glm::vec3 faceC = parseTripleFace(face3);
                    glm::vec3 faceD = parseTripleFace(face4);

                    tmpIndices.emplace_back(faceA.x - 1);
                    tmpTexCoordIndices.emplace_back(faceA.y - 1);
                    tmpNormalIndices.emplace_back(faceA.z - 1);

                    tmpIndices.emplace_back(faceB.x - 1);
                    tmpTexCoordIndices.emplace_back(faceB.y - 1);
                    tmpNormalIndices.emplace_back(faceB.z - 1);

                    tmpIndices.emplace_back(faceD.x - 1);
                    tmpTexCoordIndices.emplace_back(faceD.y - 1);
                    tmpNormalIndices.emplace_back(faceD.z - 1);

                    tmpIndices.emplace_back(faceB.x - 1);
                    tmpTexCoordIndices.emplace_back(faceA.y - 1);
                    tmpNormalIndices.emplace_back(faceA.z - 1);

                    tmpIndices.emplace_back(faceC.x - 1);
                    tmpTexCoordIndices.emplace_back(faceC.y - 1);
                    tmpNormalIndices.emplace_back(faceC.z - 1);

                    tmpIndices.emplace_back(faceD.x - 1);
                    tmpTexCoordIndices.emplace_back(faceD.y - 1);
                    tmpNormalIndices.emplace_back(faceD.z - 1);
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

    if (!tmpTexCoordIndices.empty() || !tmpNormalIndices.empty()) {
        // Utilize hashing for faster comparison of Vertex's
        struct VertexKey {
            unsigned int vertexIndex;
            int texCoordIndex;  // Use int to allow -1 for missing texture coordinates
            int normalIndex;    // Use int to allow -1 for missing normals

            bool operator==(const VertexKey &other) const {
                return vertexIndex == other.vertexIndex &&
                       texCoordIndex == other.texCoordIndex &&
                       normalIndex == other.normalIndex;
            }
        };

        struct VertexKeyHash {
            std::size_t operator()(const VertexKey &key) const {
                return ((std::hash<unsigned int>()(key.vertexIndex) ^
                         (std::hash<int>()(key.texCoordIndex) << 1)) >> 1) ^
                       (std::hash<int>()(key.normalIndex) << 1);
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
                if (key.texCoordIndex >= 0) {
                    vertex.texCoord = tmpTexCoords[key.texCoordIndex];
                }
                if (key.normalIndex >= 0) {
                    vertex.normal = tmpNormals[key.normalIndex];
                }

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
    } else {
        for (glm::vec3 v : tmpVertices) {
            this->vertexStack.addVertex(Vertex {
                    {v},
                    {0, 0},
                    {0, 0, 0}
            });
        }
        for (unsigned int indice : tmpIndices) {
            this->vertexStack.addIndex(indice);
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    this->log("Model \'" + this->modelName + "\' loaded in " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()) + "ms");
}

void Model::draw(Shader &shader) {
    this->transform.setFairingData(&shader);
    this->transform.apply();
    this->material.apply();

    this->vertexStack.draw(shader);

    this->material.unapply();
    this->transform.unapply();
}

Model::Model(const std::string& path) : modelName("missing name"), path(path), vertexStack(VertexStack<Vertex>({ 3, 2, 3 })) {
    if (!std::filesystem::exists(this->path))
        throw std::runtime_error("Model does not exist.");

    this->log("Loading model: \"" + path + "\"");
    this->loadModel();
}

Model::~Model() = default;

}; // namespace GFX