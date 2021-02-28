#ifndef GBAXX_DISPLAY_BACKGROUND_CONTROL_HPP
#define GBAXX_DISPLAY_BACKGROUND_CONTROL_HPP

#include <gba/types/int_type.hpp>

namespace gba {

enum class color_depth : bool {
    color_16 = false,
    color_256 = true,
    bpp_4 = false,
    bpp_8 = true
};

enum class affine_background_wrap : bool {
    transparent = false,
    wrap = true,
    clamp = false,
    repeat = true
};

enum class screen_size : uint16 {
    regular_32x32 = 0,
    regular_64x32 = 1,
    regular_32x64 = 2,
    regular_64x64 = 3,
    affine_16x16 = 0,
    affine_32x32 = 1,
    affine_64x64 = 2,
    affine_128x128 = 3
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
