#include "Model.hpp"
#include "IndicedVertexStack.hpp"
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace GFX {

glm::vec3 parseTripleFace(std::string face) {
    std::stringstream ss(face);
    std::string x, y, z;
    getline(ss, x, '/');
    getline(ss, y, '/');
    getline(ss, z, '/');

    unsigned int xi = -1;
    unsigned int yi = -1;
    unsigned int zi = -1;

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

    // indices are added directly because they are not inputted into the vertex shader
    // like these are.
    std::vector<unsigned int> tmpTexCoords;
    std::vector<unsigned int> tmpNormals;

    std::ifstream file(this->path);
    if (!file.is_open())
        throw std::runtime_error("Model could not be opened.");

    std::stringstream ss;
    std::string line;
    while (!file.eof()) {
        std::getline(file, line);

        ss.clear();
        ss.str(line);

        if (line.substr(0, 1) == "v") {
            char token;
            float x, y, z;

            ss >> token >> x >> y >> z;
            tmpVertices.push_back({x, y, z});
        } else if (line.substr(0, 1) == "f") {
            if (line.find("/") != std::string::npos) {
                // the format of the face is "f vertex/texCoord/normal * 4" in this case.
                // this is just ridiculous
                char token;
                std::string x, y, z, a;
                ss >> token >> x >> y >> z >> a;

                glm::vec3 xFace = parseTripleFace(x);
                this->vertexStack.addIndex(xFace.x - 1);
                tmpTexCoords.push_back(xFace.y - 1);
                tmpNormals.push_back(xFace.z - 1);

                glm::vec3 yFace = parseTripleFace(y);
                this->vertexStack.addIndex(xFace.x - 1);
                tmpTexCoords.push_back(yFace.y - 1);
                tmpNormals.push_back(yFace.z - 1);

                glm::vec3 zFace = parseTripleFace(z);
                this->vertexStack.addIndex(xFace.x - 1);
                tmpTexCoords.push_back(zFace.y - 1);
                tmpNormals.push_back(zFace.z - 1);

                glm::vec3 aFace = parseTripleFace(a);
                this->vertexStack.addIndex(xFace.x - 1);
                tmpTexCoords.push_back(aFace.y - 1);
                tmpNormals.push_back(aFace.z - 1);
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



        /*
        std::string token, x, y, z;
        ss >> token >> x >> y >> z;
        if (token == "v") {
            this->vertexStack.addVertex({{std::stof(x), std::stof(y), std::stof(z)}});
        } if (token == "f") {
            if (x.find("/") != std::string::npos) {
                //this->addTripleIndice(parseFDiv(x));
                //this->addTripleIndice(parseFDiv(y));
                //this->addTripleIndice(parseFDiv(z));
            } else {
                this->vertexStack.addIndex(std::stoi(x) - 1);
                this->vertexStack.addIndex(std::stoi(y) - 1);
                this->vertexStack.addIndex(std::stoi(z) - 1);
            }
        }*/
            
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

    for (size_t i = 0; i < tmpVertices.size(); i++) {
        this->vertexStack.addVertex({tmpVertices[i]});
    }
}

void Model::draw(Shader *shader) {
    this->vertexStack.draw(shader);
}

Model::Model(const std::string &path) : path(path), vertexStack(IndicedVertexStack()) {
    if (!std::filesystem::exists(this->path))
        throw std::runtime_error("Model does not exist.");

    this->loadModel();

    std::cout << "Loading model: " << path << "\n";
    std::cout << this->vertexStack << "\n";
}

Model::~Model() {
}

};
