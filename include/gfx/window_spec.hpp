#pragma once

#include <string_view>

namespace gfx {

struct window_spec {
    std::string_view window_title = "gfx";

    int window_width = 640;
    int window_height = 480;
};

} // namespace gfx
