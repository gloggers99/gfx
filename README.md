# GFX
## Getting Started
### What is GFX
GFX is a simple C++ graphics library that uses GLFW to create a basic multiplatform window, then provide easy to use rendering tools using the GFX:: directive.
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
## Shaders
### !!! WARNING !!!
this section needs to be rewritten as the current implementation of shaders is now easier and more efficient and the following information is outdated.
### What are shaders
Shaders are a very complex topic, the basic rundown is vertex shaders describe how to draw each vertice inputted into opengl, and the fragment shader describes how to draw each fragment/pixel of your shape, and fills it in.
### What are the default shaders
the default vertex shader simply maps the input vertices onto the gl_Position global, while the default fragment shader simply applys a basic red FragColor to the input.  
#### Default vertex shader
```glsl
#version 330

layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
```
#### Default fragment shader
```glsl
#version 330

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
```
### How can I create a custom shader
```c++
#include "path/to/GFX.hpp"

int main() {
    GFX::Shader myShader = GFX::Shader(
        /* 
            The first argument of the Shader constructor
            takes the vertex shader source. Theres many
            ways to input this, in this example I'll
            use a raw string.
        */
        R"(
            #version 330

            layout (location = 0) in vec3 aPos;

            void main() {
                gl_Position = vec4(aPos, 1.0);
            }
        )",
        /*
            The second argument is the fragment shader.
        */
        R"(
            #version 330

            out vec4 FragColor;

            void main() {
                FragColor = vec4(1.0, 0.0, 0.0, 1.0);
            }
        )"
    );
}
```
