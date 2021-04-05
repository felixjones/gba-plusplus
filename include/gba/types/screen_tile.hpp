#ifndef GBAXX_TYPES_SCREEN_TILE_HPP
#define GBAXX_TYPES_SCREEN_TILE_HPP

#include <gba/types/int_type.hpp>

namespace gba {

enum class tile_flip : uint8 {
    none = 0,
    horizontal = 1,
    vertical = 2,
    both = 3
};

struct screen_tile {
    uint16 tile_index : 10;
    tile_flip flip : 2;
    uint16 palette_bank : 4;
};

static_assert( sizeof( screen_tile ) == 2, "screen_tile must be tightly packed" );

} // gba

#endif // define GBAXX_TYPES_SCREEN_TILE_HPP
