#include "ShaderWatcher.hpp"
#include <iostream>

namespace GFX {

void ShaderWatcher::attach(Shader &shader) {
    shaders.push_back(&shader);
}

void ShaderWatcher::checkShaders() {
    // fetch source code into these 2 tmp variables
    // if they differ from the new fetched source code
    // then recompile.
    std::string vertexSource, fragmentSource;

    for (auto *shader : shaders) {
        vertexSource = shader->vertexSource;
        fragmentSource = shader->fragmentSource;
        
        shader->fetchSource();
        
        if (vertexSource != shader->vertexSource || fragmentSource != shader->fragmentSource) {
            if (!shader->recompile())
                std::cerr << "Shader change detected, but recompilation failed.\n";
        }
    }
}

ShaderWatcher::ShaderWatcher() {
}

ShaderWatcher::~ShaderWatcher() {
}

}; // namespace GFX
