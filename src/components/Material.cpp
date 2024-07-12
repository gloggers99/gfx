#include "Material.hpp"
#include "hermes/hermes.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

namespace GFX {

void Material::bindMaps() {
    this->ambientMap.bind();
    this->diffuseMap.bind();
    this->specularMap.bind();
    this->specularHighlightMap.bind();
    this->alphaMap.bind();
}

void Material::unbindMaps() {
    this->ambientMap.unbind();
    this->diffuseMap.unbind();
    this->specularMap.unbind();
    this->specularHighlightMap.unbind();
    this->alphaMap.unbind();
}

void Material::apply() {
    this->bindMaps();
}

void Material::unapply() {
    this->unbindMaps();
}

Material::Material(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open())
        throw std::runtime_error("Material file not found or couldn't be opened: \"" + path + "\"");

    // man i was tweaking out when i wrote this wtf
    std::string workDirectory;

    std::string tmpString;
    std::string revPath = path;
    std::reverse(revPath.begin(), revPath.end());
    std::stringstream tmpStream(revPath);
    std::getline(tmpStream, tmpString, '/');
    std::getline(tmpStream, workDirectory);
    std::reverse(workDirectory.begin(), workDirectory.end());
    workDirectory = workDirectory + "/";

    std::string line;
    while (std::getline(file, line)) {
        // trim end of string
        while (!line.empty() && isspace(line.back())) line.pop_back();

        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        // ambient
        if (prefix == "Ka") {
            ss >> this->ambient.x >> this->ambient.y >> this->ambient.z;
        }
        // diffuse
        else if (prefix == "Kd") {
            ss >> this->diffuse.x >> this->diffuse.y >> this->diffuse.z;
        }
        // specular
        else if (prefix == "Ks") {
            ss >> this->specular.x >> this->specular.y >> this->specular.z;
        }
        // specular exponent
        else if (prefix == "Ns") {
            ss >> this->specularExponent;
        }
        // dissolve
        else if (prefix == "d") {
            ss >> this->dissolve;
        }
        // optical density
        else if (prefix == "Ni") {
            ss >> this->opticalDensity;
        }
        // illumination model
        else if (prefix == "illum") {
            int model;
            ss >> model;
            this->illuminationModel = static_cast<IlluminationModel>(model);
        }
        // ambientMap
        else if (prefix == "map_Ka") {
            std::string mapPath;
            ss >> mapPath;
            this->ambientMap.loadPath(workDirectory + mapPath);
        }
        // diffuseMap
        else if (prefix == "map_Kd") {
            std::string mapPath;
            ss >> mapPath;
            this->diffuseMap.loadPath(workDirectory + mapPath);
        }
        // specularMap
        else if (prefix == "map_Ks") {
            std::string mapPath;
            ss >> mapPath;
            this->specularMap.loadPath(workDirectory + mapPath);
        }
        // specularHighlightMap
        else if (prefix == "map_Ns") {
            std::string mapPath;
            ss >> mapPath;
            this->specularHighlightMap.loadPath(workDirectory + mapPath);
        }
        // alphaMap
        else if (prefix == "map_d") {
            std::string mapPath;
            ss >> mapPath;
            this->alphaMap.loadPath(workDirectory + mapPath);
        }
    }
}

Material::Material() {}

Material::~Material() = default;

} // namespace GFX