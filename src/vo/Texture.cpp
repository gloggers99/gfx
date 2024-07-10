#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stdexcept>

namespace GFX {

GLuint Texture::get() {
    return this->texture;
}

void Texture::setSlot(GLenum slot) {
    this->slot = slot;
}

GLenum Texture::getSlot() {
    return this->slot;
}

void Texture::bind() {
    glActiveTexture(this->slot);
    glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Texture::unbind() {
    glActiveTexture(this->slot);
    glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Texture::loadPath(const std::string &path, bool flipVertically) {
    if (flipVertically)
        stbi_set_flip_vertically_on_load(true);

    int width, height, componentCount;

    unsigned char *data = stbi_load(path.c_str(), &width, &height, &componentCount, 0);

    if (data) {
        GLenum format;
        if (componentCount == 1)
            format = GL_RED;
        else if (componentCount == 3)
            format = GL_RGB;
        else if (componentCount == 4)
            format = GL_RGBA;
        else throw std::runtime_error("Invalid image format!");

        this->bind();
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        this->unbind();

        stbi_image_free(data);

        this->loaded = true;
    } else {
        stbi_image_free(data);
        throw std::runtime_error("Failed to load texture at path: \"" + path + "\"");
    }
}

bool Texture::isLoaded() {
    return this->loaded;
}

Texture::Texture(GLenum slot) : slot(slot), loaded(false) {
    glGenTextures(1, &this->texture);
}

Texture::~Texture() {
    glDeleteTextures(1, &this->texture);
}

} // namespace GFX