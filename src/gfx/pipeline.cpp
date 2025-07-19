#include <gfx/pipeline.hpp>

#include <gfx/core.hpp>

namespace gfx {

    pipeline_status pipeline::update(const core &core_instance) {
        return pipeline_status::CONTINUE;
    }

} // namespace gfx
