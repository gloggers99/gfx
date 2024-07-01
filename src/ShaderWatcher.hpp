#include "Shader.hpp"

#include <vector>

namespace GFX {

/*
    By design I wanted this to be multithreaded, unfortunately opengl does not play nice with multithreading.
    So this is a single threaded solution where you have to call checkShaders() every frame. The downside is 
    that a file is read every frame, which doesn't seem to be a huge problem on my machine. But it might be on
    lower end machines. I will have to look into a better solution for this.
 */

class ShaderWatcher {
private:
    std::vector<Shader*> shaders;

public:
    void attach(Shader &shader);
    void checkShaders();

    ShaderWatcher();
    ~ShaderWatcher();
};

}; // namespace GFX
