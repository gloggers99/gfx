#pragma once

#include "../Shader.hpp"

namespace GFX {

class IShaderWatcher {
public:
    virtual void attach(Shader *shader) = 0;
    virtual void checkShaders() = 0;
};

}; // namespace GFX