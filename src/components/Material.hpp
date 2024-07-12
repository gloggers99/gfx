#pragma once

#include "IFairing.hpp"

#include "../vo/Texture.hpp"
#include "../Shader.hpp"

#include <string>
#include <vector>

#include "glm/glm/glm.hpp"

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

class Material : IFairing<void> {
public:
    glm::vec3 ambient, diffuse, specular;
    float specularExponent, dissolve, opticalDensity;
    IlluminationModel illuminationModel;

    Texture ambientMap = Texture(GL_TEXTURE0);
    Texture diffuseMap = Texture(GL_TEXTURE1);
    Texture specularMap = Texture(GL_TEXTURE2);
    Texture specularHighlightMap = Texture(GL_TEXTURE3);
    Texture alphaMap = Texture(GL_TEXTURE4);

    /** Bind all the texture maps available
     *
     */
    void bindMaps();

    /** Unbind all the texture maps available
     *
     */
    void unbindMaps();

    void apply() override;
    void unapply() override;

    explicit Material(const std::string& path);
    Material();
    ~Material();
};

} // namespace GFX
