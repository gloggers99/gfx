/// 
/// gfx_test is used to test the gfx library code in many different ways.
/// Most of the time it will just be random code I throw together.
///

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <gfx/pipeline.hpp>
#include <gfx/core.hpp>

#include <iostream>

class test_pipeline : public gfx::pipeline {
public:
    ~test_pipeline() override = default;

    gfx::pipeline_status update(const gfx::core &core_instance) override {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        return gfx::pipeline_status::CONTINUE;
    }
};

int main(int argc, char *argv[]) {
    std::cout << "gfx_test\n";

    gfx::core core { };
    core.set_pipeline<test_pipeline>();
    core.run_pipeline();

    return 0;
}
