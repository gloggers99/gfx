#include "ShaderWatcher.hpp"

#include <iostream>

#include <unistd.h>
#include <sys/inotify.h>

namespace GFX {

void ShaderWatcher::attach(Shader &shader) {
    this->shaders.push_back(&shader);

}

ShaderWatcher::ShaderWatcher() {
    std::vector<Shader*> *shaders = &this->shaders;

    auto watcherFunction = [shaders]() {
        int fd = inotify_init();
        if (fd < 0) {
            std::cerr << "inotify_init failed\n";
            return;
        }

        int wd = inotify_add_watch(fd, "shaders", IN_MODIFY);
        if (wd < 0) {
            std::cerr << "inotify_add_watch failed\n";
            return;
        }

        char buffer[4096];
        while (true) {
            int length = read(fd, buffer, 4096);
            if (length < 0) {
                std::cerr << "read failed\n";
                return;
            }

            int i = 0;
            while (i < length) {
                struct inotify_event *event = (struct inotify_event *) &buffer[i];
                if (event->mask & IN_MODIFY) {
                    // check if the file is in any attached shaders:
                    for (Shader *shader : *shaders) {
                        if (shader->shaderName + ".vert" == event->name || shader->shaderName + ".frag" == event->name) {
                            std::cout << "recompiling shader\n";
                            shader->recompile();
                        }
                    }
                    std::cout << "file modified: " << event->name << "\n";
                }
                i += sizeof(struct inotify_event) + event->len;
            }
        }

    };

    this->watcherThread = std::thread(watcherFunction);
}

ShaderWatcher::~ShaderWatcher() {
    this->watcherThread.detach();
}

}; // namespace GFX
