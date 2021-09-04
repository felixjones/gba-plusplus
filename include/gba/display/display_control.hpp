#ifndef GBAXX_DISPLAY_DISPLAY_CONTROL_HPP
#define GBAXX_DISPLAY_DISPLAY_CONTROL_HPP

#include <gba/types/int_type.hpp>

namespace gba {
/**
 * Object namespace
 */
namespace object {

/**
 * Object tile mapping mode
 *
 * See display_control.object_tile_map
 */
enum class tile_map : bool {
    two_dimensional = false, ///< Object tiles are arranged as a tile-map in memory
    one_dimensional = true, ///< Object tiles are arranged sequentially in memory
    linear = true ///< alias of one_dimensional
};

} // object

/**
 * OAM access mode
 *
 * See display_control.oam_hblank_access
 */
enum class oam_hblank_access : bool {
    locked = false, ///< OAM memory cannot be modified during hblank
    unlocked = true ///< OAM can be modified during hblank
};

/**
 * Base implementation of display_control
 */
struct display_control {
    /// Display mode (0, 1, 2, 3, 4 or 5)
    uint16 mode : 3;
    /// Read-only flag for CGB mode
    bool color_game_boy : 1;
    /// Currently displayed page (available only with mode 3 or 5)
    uint16 page : 1;
    /// OAM registers writable during hblank
    gba::oam_hblank_access oam_hblank_access : 1;
    /// Object tile mapping mode
    object::tile_map object_tile_map : 1;
    bool force_blank : 1, ///< Turn off display
        layer_background_0 : 1, ///< Enable background layer 0
        layer_background_1 : 1, ///< Enable background layer 1
        layer_background_2 : 1, ///< Enable background layer 2
        layer_background_3 : 1, ///< Enable background layer 3
        layer_object : 1, ///< Enable object layer
        window_0 : 1, ///< Enable window 0
        window_1 : 1, ///< Enable window 1
        window_object : 1; ///< Enable object window

    /**
     * Flips the value of display_control.page
     * @return this
     */
    display_control& flip_page() noexcept {
        page ^= 1;
        return *this;
    }
};

static_assert( sizeof( display_control ) == 2, "display_control must be tightly packed" );

/**
 * Undocumented types
 */
namespace undocumented {

/**
 * Green-swap mode
 */
enum class green_swap : uint16 {
    normal = 0, ///< disabled
    swap = 1 ///< enabled
};

static_assert( sizeof( green_swap ) == 2, "green_swap must be size 2" );

} // undocumented
} // gba

#endif // define GBAXX_DISPLAY_DISPLAY_CONTROL_HPP
