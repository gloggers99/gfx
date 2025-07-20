#pragma once

#include <GLFW/glfw3.h>

#include <memory>
#include <utility>

#include "gfx/pipeline.hpp"
#include "window_spec.hpp"

namespace gfx {

    using glfw_window = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;

    ///
    /// The "core" of gfx, needed for pretty much everything.
    ///
    /// Originally gfx.hpp was a metaclass which imported
    /// every other class and feature of gfx. Now we will
    /// stick to object oriented programming.
    ///
    class core {
        /// Triggered on GLFW error.
        static void error_callback(int error, const char *description);

        glfw_window window;

        std::unique_ptr<pipeline> current_pipeline;

    public:
        core(const window_spec &spec = {});
        ~core();

        /// Set the current pipeline.
        /// @tparam pipeline_type Type of the pipeline inherited class.
        /// @param pipeline_args Optional arguments to pass to the
        ///                      pipeline inherited class constructor.
        template<typename pipeline_type, typename ...pipeline_args_types>
        void set_pipeline(pipeline_args_types &&...pipeline_args) {
            auto new_pipeline = std::make_unique<pipeline_type>();

            this->current_pipeline = std::move(new_pipeline);
        }

        void run_pipeline();
    };

} // namespace gfx
