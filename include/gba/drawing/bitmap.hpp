#ifndef GBAXX_DRAWING_BITMAP_HPP
#define GBAXX_DRAWING_BITMAP_HPP

#include <gba/types/int_type.hpp>

namespace gba {

template <typename BitmapDef>
struct bitmap : BitmapDef {
    void put_pixel( int x, int y, typename BitmapDef::pixel_type color ) noexcept {
        BitmapDef::put_pixel( x, y, color );
    }
};

} // gba

#endif // define GBAXX_DRAWING_BITMAP_HPP
