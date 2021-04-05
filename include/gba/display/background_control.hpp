#ifndef GBAXX_DISPLAY_BACKGROUND_CONTROL_HPP
#define GBAXX_DISPLAY_BACKGROUND_CONTROL_HPP

#include <gba/types/color.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/screen_size.hpp>

namespace gba {

enum class affine_background_wrap : bool {
    transparent = false,
    wrap = true,
    clamp = false,
    repeat = true
};

struct background_control {
    uint16 priority : 2,
        character_base_block : 2,
        : 2;
    bool mosaic : 1;
    gba::color_depth color_depth : 1;
    uint16 screen_base_block : 5;
    gba::affine_background_wrap affine_background_wrap : 1;
    gba::screen_size screen_size : 2;
};

static_assert( sizeof( background_control ) == 2, "background_control must be tightly packed" );

} // gba

#endif // define GBAXX_DISPLAY_BACKGROUND_CONTROL_HPP
