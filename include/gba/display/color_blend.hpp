#ifndef GBAXX_DISPLAY_COLOR_BLEND_HPP
#define GBAXX_DISPLAY_COLOR_BLEND_HPP

#include <gba/types/int_type.hpp>
#include <gba/types/fixed_point.hpp>
#include <gba/types/fixed_point_make.hpp>

namespace gba {

enum class blend_mode : uint8 {
    off = 0,
    standard = 1,
    white = 2,
    black = 3,

    alpha = standard,
    brightness_increase = white,
    brightness_decrease = black
};

struct blend_control {
    bool src_bg0 : 1,
        src_bg1 : 1,
        src_bg2 : 1,
        src_bg3 : 1,
        src_obj : 1,
        src_backdrop : 1;
    blend_mode mode : 2;
    bool dst_bg0 : 1,
        dst_bg1 : 1,
        dst_bg2 : 1,
        dst_bg3 : 1,
        dst_obj : 1,
        dst_backdrop : 1;
    uint8 : 2;
};

static_assert( sizeof( blend_control ) == 2, "blend_control must be tightly packed" );

struct blend_alpha {
    make_ufixed<4, 4> eva;
    make_ufixed<4, 4> evb;
};

static_assert( sizeof( blend_alpha ) == 2, "blend_alpha must be tightly packed" );

} // gba

#endif // define GBAXX_DISPLAY_COLOR_BLEND_HPP
