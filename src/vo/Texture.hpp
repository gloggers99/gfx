#pragma once

#include "IVO.hpp"

#include <string>

namespace GFX {

class Texture : IVO {
private:
    GLuint texture;

public:
    GLuint get() override;

    void bind() override;
    void unbind() override;

    void loadPath(const std::string &path);

    Texture();
    ~Texture();
};

} // namespace GFX
