#include "Shader.hpp"

#ifndef _WIN32
#define

#include <map>
#include <mutex>
#include <thread>

#include <sys/inotify.h>

namespace GFX {

/*
    By design I wanted this to be multithreaded, unfortunately opengl does not play nice with multithreading.
    So this is a single threaded solution where you have to call checkShaders() every frame. The downside is 
    that a file is read every frame, which doesn't seem to be a huge problem on my machine. But it might be on
    lower end machines. I will have to look into a better solution for this.
 */

/*
 * UPDATE: I am working on a multithreaded approach using inotify again..
 */

/*
 * Multithreading is now working but it is limited to linux only for now.
 */

class ShaderWatcher {
private:
    std::thread shaderWatcherThread;
    
    std::map<Shader *, bool> shaders;
    std::mutex shadersLock;

public:
    void attach(Shader &shader);
    void checkShaders();

    ShaderWatcher();
    ~ShaderWatcher();
};

}; // namespace GFX

#endif