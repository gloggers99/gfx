#include "Texture.hpp"
#include "Renderer.hpp"

#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace GFX {

GLuint Texture::getTexture() {
    return this->texture;
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->texture);
}

Texture::Texture(std::string texturePath) {
    if (!std::filesystem::exists(texturePath))
        throw std::runtime_error("texture file: \'" + texturePath + "\' doesn't exist");

    int width, height, channels;
    this->data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
    if (!this->data)
        throw std::runtime_error("failed to load texture: " + texturePath);

    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // TODO: texture filtering is disabled here, 
    //       modification of the texture class will need to be done in the future.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->data);
    glGenerateMipmap(GL_TEXTURE_2D);

}

Texture::~Texture() {
    stbi_image_free(this->data);
    glDeleteTextures(1, &this->texture);
}

}; // namespace GFX
