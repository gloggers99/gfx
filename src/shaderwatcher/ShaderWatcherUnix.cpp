#if not defined(__MINGW32__)

#include "ShaderWatcherUnix.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/inotify.h>

namespace GFX {

void ShaderWatcher::attach(Shader *shader) {
    shaders.insert(std::pair<Shader *, bool>(&shader, false));
}

void ShaderWatcher::checkShaders() {
    // old implementation which read a file each frame:
    /*
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
    */

    shadersLock.lock();
    for (auto &shader : shaders) {
        if (shader.second) {
            if (!shader.first->recompile())
                std::cerr << "Shader change detected, but recompilation failed.\n";
            shader.second = false;
        }
    }
    shadersLock.unlock();
}

ShaderWatcher::ShaderWatcher() {
    auto watcher = [&]() {
        int fd = inotify_init();
        if (fd < 0) {
            std::cerr << "Failed to initialize inotify.\n";
            return;
        }

        int wd = inotify_add_watch(fd, "shaders", IN_MODIFY);
        if (wd < 0) {
            std::cerr << "Failed to add watch.\n";
            return;
        }

        char buffer[4096];
        while (true) {
            int length = read(fd, buffer, 4096);
            if (length < 0) {
                std::cerr << "Failed to read inotify event.\n";
                return;
            }

            int i = 0;
            while (i < length) {
                struct inotify_event *event = (struct inotify_event *) &buffer[i];
                if (event->mask & IN_MODIFY) {

                    std::string shaderName;
                    std::stringstream ss(event->name);
                    std::getline(ss, shaderName, '.');

                    this->shadersLock.lock();
                    for (auto &shader : this->shaders) {
                        if (shader.first->shaderName == shaderName) {
                            shader.second = true;
                        }
                    }
                    this->shadersLock.unlock();
                }
                i += sizeof(struct inotify_event) + event->len;
            }
        }
    };

    this->shaderWatcherThread = std::thread(watcher);
}

ShaderWatcher::~ShaderWatcher() {
    this->shaderWatcherThread.detach();
}

}; // namespace GFX

#endif