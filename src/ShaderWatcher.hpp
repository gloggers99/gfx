#include "Shader.hpp"

#include <thread>
#include <vector>

namespace GFX {

/*
    The idea of ShaderWatcher is to auto recompile attached shaders when the source files change.

    TODO: make this cross platform, currently we use inotify which is linux exclusive.
 */

class ShaderWatcher {
private:
    std::vector<Shader*> shaders;
    std::thread watcherThread;

public:
    void attach(Shader &shader);

    ShaderWatcher();
    ~ShaderWatcher();
};

}; // namespace GFX
