#ifndef GBAXX_DISPLAY_MOSCAIC_HPP
#define GBAXX_DISPLAY_MOSCAIC_HPP

#include <gba/types/dimension.hpp>

namespace gba {

struct mosaic_size {
    dimension background;
    dimension object;
    uint16 : 16;
};

static_assert( sizeof( mosaic_size ) == 4, "mosaic_size must be aligned to 4 bytes" );

} // gba

#endif // define GBAXX_DISPLAY_MOSCAIC_HPP
