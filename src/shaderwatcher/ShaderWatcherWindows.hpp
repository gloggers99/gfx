#pragma once

#include "../Shader.hpp"
#include "IShaderWatcher.h"

#include <map>
#include <mutex>
#include <thread>

namespace GFX {

class ShaderWatcher : IShaderWatcher {
private:
    std::thread shaderWatcherThread;

    std::map<Shader *, bool> shaders;
    std::mutex shadersLock;
public:
    void attach(GFX::Shader *shader) override;
    void checkShaders() override;

    ShaderWatcher();
    ~ShaderWatcher();
};

} // namespace GFX

