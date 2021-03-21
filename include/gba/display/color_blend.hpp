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
    alpha = standard
};

struct blend_control {
    bool top_bg0 : 1,
        top_bg1 : 1,
        top_bg2 : 1,
        top_bg3 : 1,
        top_obj : 1;
    blend_mode mode : 2;
    bool bot_bg0 : 1,
        bot_bg1 : 1,
        bot_bg2 : 1,
        bot_bg3 : 1,
        bot_obj : 1;
    uint8 : 2;
};

static_assert( sizeof( blend_control ) == 2, "blend_control must be tightly packed" );

struct blend_alpha {
    make_ufixed<1, 4> eva;
    make_ufixed<1, 4> evb;
};

static_assert( sizeof( blend_alpha ) == 2, "blend_alpha must be tightly packed" );

struct blend_gamma {
    make_ufixed<1, 4> ey;
    uint8 : 8;
};

static_assert( sizeof( blend_gamma ) == 2, "blend_gamma must be tightly packed" );

} // gba

#endif // define GBAXX_DISPLAY_COLOR_BLEND_HPP
