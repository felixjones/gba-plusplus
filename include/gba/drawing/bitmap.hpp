#ifndef GBAXX_DRAWING_BITMAP_HPP
#define GBAXX_DRAWING_BITMAP_HPP

#include <gba/types/int_type.hpp>

namespace gba {

template <typename BitmapDef>
struct bitmap : BitmapDef {
    using pixel_type = typename BitmapDef::pixel_type;

    void put_pixel( int x, int y, pixel_type color ) noexcept {
        BitmapDef::put_pixel( x, y, color );
    }

    static void clear_to_color( pixel_type color ) noexcept {
        BitmapDef::clear_to_color( color );
    }

    static void rect_fill( int x1, int y1, int x2, int y2, pixel_type color ) noexcept {
        BitmapDef::rect_fill( x1, y1, x2, y2, color );
    }

    static void rect( int x1, int y1, int x2, int y2, pixel_type color ) noexcept {
        BitmapDef::rect( x1, y1, x2, y2, color );
    }

    static void line( int x1, int y1, int x2, int y2, pixel_type color ) noexcept {
        BitmapDef::line( x1, y1, x2, y2, color );
    }

    static void clear() noexcept {
        BitmapDef::clear();
    }
};

} // gba

#endif // define GBAXX_DRAWING_BITMAP_HPP
