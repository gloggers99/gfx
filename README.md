# GFX
## Getting Started
### README NEEDS TO BE REDONE, EVERYTHING HAS BEEN REWORKED
### What is GFX
GFX is a simple C++ graphics library that uses GLFW to create a basic multiplatform window, then provide easy to use rendering tools using the GFX:: directive.
![](assets/shaderwatchertest.gif)
<sub><sup>Automatic shader hot reloading showcase</sup></sub>
### Features
- [X] Easy to use VAO, VBO, and EBO classes
- [ ] Texture System (needs to be redone)
- [X] Automatic hot reloadable shader compilation
- [X] Compatibility with ALL custom opengl drawing code (theoretically you could use GFX to load OpenGL then use OpenGL code to do the rest)
- [X] Full ImGui implementation
### Hello World
Our hello world consists of creating a renderer object, defining our render function, and passing it into the renderer.
```c++
#include "path/to/GFX.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();

    /*
        we create an anonymous function to declare
        our rendering:
    */
    auto draw = [&renderer](float deltaTime) {
        renderer.clear();
        renderer.clearColor(0.2, 0.3, 0.3, 1.0);

        renderer.swapBuffers();
    };

    /*
        then we pass it into the renderer for it to 
        loop our function with some extra additions,
        to be specific, the renderer will automatically
        calculate deltaTime (the time in between each frame),
        and manage glfw events. 

        (see GFX::Renderer::loop for more info)
    */
    renderer.loop(draw);

    return 0;
}
```
### The basic triangle
OpenGL hello world tutorials seem to love drawing a triangle as your first task, here would be the equivalent using GFX.
```c++
#include "path/to/GFX.hpp"

int main() {
    GFX::Renderer renderer = GFX::Renderer();

    /*
        You SHOULD create your own shaders by 
        passing in a vertex shader source string
        and a fragment shader source string into
        the GFX::Shader() constructor. However the
        default is sufficient enough to render our 
        triangle. The default shaders are described 
        in the following section.
    */
    GFX::Shader shader = GFX::Shader();

    float vertices[] = {
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.0, 0.5, 0.0
    };

    /*
        VAO's and VBO's are explained in depth in
        numerous sources, basic 3D programming knowledge
        is optional here, however an understanding will
        make your experience MUCH better and easier.
    */
    GFX::VAO vao = GFX::VAO();
    GFX::VBO vbo = GFX::VBO();

    vao.bind();
    vbo.bind();
    vbo.setBufferData(vertices, sizeof(vertices));
    vbo.setAttribPointer(0, 3, 3 * sizeof(float), 0);
    vao.unbind();

    auto draw = [&renderer, &shader, &vao](float deltaTime) {
        renderer.clear();
        renderer.clearColor(0.2f, 0.3f, 0.3f, 1.0f);

        /*
            If you're new to how opengl works, you need a shader
            active in order to draw any vertices or buffers to the
            screen.
        */
        shader.use();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.unbind();

        renderer.swapBuffers();
    };

    renderer.loop(draw);

    return 0;
}
```
### A more structured example
This is more useful for larger projects when you have many different variables to send into the render function.
```c++
#include "../src/GFX.hpp"

struct app {
    GFX::Renderer *renderer;
} typedef App;

int main() {
    GFX::Renderer renderer = GFX::Renderer();

    App app = {
        &renderer
    };

    auto draw = [&app](float deltaTime) {
        app.renderer->clear();
        app.renderer->clearColor(0.2f, 0.3f, 0.3f, 1.0f);
        app.renderer->swapBuffers();
    };

    renderer.loop(draw);

    return 0;
}
```
In the end how you structure your code is up to you, but the above example is a good starting point for larger projects. You could even skip the lambda function and straight up pass a normal function into the renderer.
## Shaders
!!! the shader system has been reworked and this section is going to be rewritten.
