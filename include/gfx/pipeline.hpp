#pragma once

namespace gfx {
    class core;

    enum class pipeline_status {
        CONTINUE,
        BREAK
    };

    class pipeline {
    public:
        pipeline();
        virtual ~pipeline();
        
        /// This pipeline operation is called every frame.
        virtual pipeline_status update(const core &core_instance);
    };

} // namespace gfx
