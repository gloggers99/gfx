#pragma once

#include "vo/Texture.hpp"

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace GFX {

// these are almost NEVER specified in the MTL files
enum class IlluminationModel {
    COLOR = 0,
    AMBIENT = 1,
    HIGHLIGHT = 2,
    REFLECTION_RAY_TRACE = 3,
    TRANSPARENCY_GLASS_RAY_TRACE = 4,
    REFLECTION_FRESNEL_RAY_TRACE = 5,
    TRANSPARENCY_RAY_TRACE = 6,
    TRANSPARENCY_FRESNEL_RAY_TRACE = 7,
    REFLECTION = 8,
    TRANSPARENCY_GLASS = 9,
    INVIS_SHADOW = 10
};

// this is designed to load a blender MTL file.
// however if youre a psychopath you can populate
// it yourself;

// this was written in less than an hour, im actually insane

class Material {
public:
    glm::vec3 ambient, diffuse, specular;
    float specularExponent, dissolve, opticalDensity;
    IlluminationModel illuminationModel;

    Texture ambientMap, diffuseMap, specularMap, specularHighlight, alphaMap;

    explicit Material(std::string path);
    Material();
    ~Material();
};

} // namespace GFX
