#ifndef GBAXX_DISPLAY_DISPLAY_CONTROL_HPP
#define GBAXX_DISPLAY_DISPLAY_CONTROL_HPP

#include <gba/types/int_type.hpp>

namespace gba {

enum class oam_hblank_access : bool {
    locked = false,
    unlocked = true
};

enum class object_tile_map : bool {
    two_dimensional = false,
    one_dimensional = true,
    linear = true
};

struct display_control {
    uint16 mode : 3;
    bool color_game_boy : 1;
    uint16 page : 1;
    gba::oam_hblank_access oam_hblank_access : 1;
    gba::object_tile_map object_tile_map : 1;
    bool force_blank : 1,
            layer_background_0 : 1,
            layer_background_1 : 1,
            layer_background_2 : 1,
            layer_background_3 : 1,
            layer_object : 1,
            window_0 : 1,
            window_1 : 1,
            window_object : 1;

    display_control& flip_page() noexcept {
        page ^= 1;
        return *this;
    }
};

static_assert( sizeof( display_control ) == 2, "display_control must be tightly packed" );

} // gba

#endif // define GBAXX_DISPLAY_DISPLAY_CONTROL_HPP
