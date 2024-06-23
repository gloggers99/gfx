# GFX
## Getting Started
### What is GFX
GFX is a simple C++ graphics library that uses GLFW to create a basic multiplatform window, then provide easy to use rendering tools using the GFX:: directive.
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
    auto draw = [&renderer](int deltaTime) {
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
