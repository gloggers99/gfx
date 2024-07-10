#pragma once

#include "IVO.hpp"

#include <string>

namespace GFX {

class Texture : IVO {
private:
    GLuint texture;
    GLenum slot;
    bool loaded;

public:
    GLuint get() override;

    void setSlot(GLenum slot);
    GLenum getSlot();

    void bind() override;
    void unbind() override;

    void loadPath(const std::string &path, bool flipVertically = true);
    bool isLoaded();

    explicit Texture(GLenum slot = GL_TEXTURE0);
    ~Texture();
};

} // namespace GFX
