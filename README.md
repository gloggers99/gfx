

<div align="center">

<img src="assets/gfx.png" alt="banner" width="300">

<br />

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](https://forthebadge.com)
</div>

<!--toc:start-->
- [Getting Started](#getting-started)
  - [What is GFX](#what-is-gfx)
  - [Features](#features)
  - [Hello World](#hello-world)
  - [Shader Watcher Example](#shader-watcher-example)
  - [OBJ Loader](#obj-loader)
<!--toc:end-->

## Getting Started
### What is GFX
GFX is a simple C++ graphics library that uses GLFW to create a basic multiplatform window, then provide easy to use rendering tools using the GFX:: directive.
![](assets/shaderwatchertest.gif)
<sub><sup>Automatic shader hot reloading showcase</sup></sub>
### Features
- [X] Easy to use VAO, VBO, and EBO classes
- [X] .OBJ file importer made from scratch built for efficiency
- [ ] Texture System (needs to be redone)
- [X] Multithreaded automatic hot reloadable shader compilation
- [X] Compatibility with ALL custom opengl drawing code (theoretically you could use GFX to load OpenGL then use OpenGL code to do the rest)
- [X] Full ImGui implementation
### Hello World
```cpp
#include <GFX.h>

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Shader shader = GFX::Shader("defaultShader");
    GFX::Camera camera = GFX::Camera();

    // the definition of a vertex is subject to change.
    std::vector<GFX::Vertex> vertices = {
        {{0.5, -0.5, 0.0}},
        {{-0.5, -0.5, 0.0}},
        {{0.0, 0.5, 0.0}}
    };

    GFX::VertexStack stack = GFX::VertexStack(vertices);

    auto draw = [&](float deltaTime) {
        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));
        stack.draw(&shader);
    };

    renderer.loop(draw);

    return 0;
}
```
![](assets/helloworld.png)
### Shader Watcher Example
Shader Watcher is a feature that automatically reloads shaders when the source code for them is changed. This is incredibly useful for debugging shaders as you can see the changes in real-time.
```cpp
#include <GFX.h>

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Camera camera = GFX::Camera();

    GFX::Shader shader = GFX::Shader("defaultShader");

    /*
        Shader Watcher runs on a seperate thread and checks for file changes using inotify,
        this is linux only for now, but I plan to add windows support soon. Shader Watcher will 
        ONLY watch the shaders you explicitly attach.
    */
    GFX::ShaderWatcher watcher = GFX::ShaderWatcher();
    watcher.attach(&shader);


    // the definition of a vertex is subject to change.
    std::vector<GFX::Vertex> vertices = {
        {{0.5, -0.5, 0.0}},
        {{-0.5, -0.5, 0.0}},
        {{0.0, 0.5, 0.0}}
    };

    GFX::VertexStack stack = GFX::VertexStack(vertices);

    auto draw = [&](float deltaTime) {
        // each frame you must call checkShaders to recompile the changed shaders.
        watcher.checkShaders();
        
        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));
        stack.draw(&shader);
    };

    renderer.loop(draw);

    return 0;
}
```
### OBJ Loader
```cpp
#include <GFX.h>

int main() {
    GFX::Renderer renderer = GFX::Renderer();
    GFX::Shader shader = GFX::Shader("defaultShader");
    GFX::Camera camera = GFX::Camera();

    /*
        GFX::Model uses IndicedVertexStack underneath. As of right now only
        .obj files are supported, however more formats will be supported in
        the future.

    */
    GFX::Model model = GFX::Model("path/to/file.obj");

    auto draw = [&](float deltaTime) {
        shader.updateUniform("camera", camera.createCameraMatrix(&renderer));
        // scale the model down a bit
        shader.updateUniform("transform", glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f)));

        model.draw(&shader);
    };

    renderer.loop(draw);

    return 0;
}
```
