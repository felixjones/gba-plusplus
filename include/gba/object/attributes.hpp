#ifndef GBAXX_OBJECT_ATTRIBUTES_HPP
#define GBAXX_OBJECT_ATTRIBUTES_HPP

#include <gba/types/color.hpp>
#include <gba/types/fixed_point.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/matrix.hpp>

namespace gba {
namespace object {

using mat2 = mat2<fixed_point<int16, -8>>;

enum class mode : uint16 {
    regular = 0,
    affine = 1,
    hidden = 2,
    affine_double = 3
};

enum class gfx_mode : uint16 {
    normal = 0,
    blending = 1,
    windowed = 2
};

enum class shape : uint16 {
    square = 0,
    wide = 1,
    tall = 2
};

struct attr0 {
    uint16 y : 8;
    mode object_mode : 2;
    object::gfx_mode gfx_mode : 2;
    bool mosaic : 1;
    color_depth color_mode : 1;
    object::shape shape : 2;
};

struct attr1_regular {
    uint16 x : 9,
        : 3;
    bool flip_horizontal : 1,
        flip_vertical : 1;
    uint16 size : 2;
};

struct attr1_affine {
    uint16 x : 9,
        affine_index : 5,
        size : 2;
};

struct attr2 {
    uint16 tile_index : 10,
        priority : 2,
        palette_bank : 4;
};

static constexpr auto tile_width( const object::shape shape, const uint32 size ) noexcept {
    switch ( shape ) {
        case shape::square:
            switch ( size ) {
                case 0:
                    return 1;
                case 1:
                    return 2;
                case 2:
                    return 4;
                case 3:
                    return 8;
                default:
                    return 0;
            }
        case shape::wide:
            switch ( size ) {
                case 0:
                    return 2;
                case 1:
                    return 4;
                case 2:
                    return 4;
                case 3:
                    return 8;
                default:
                    return 0;
            }
        case shape::tall:
            switch ( size ) {
                case 0:
                    return 1;
                case 1:
                    return 1;
                case 2:
                    return 2;
                case 3:
                    return 4;
                default:
                    return 0;
            }
        default:
            return 0;
    }
}

static constexpr auto tile_height( const object::shape shape, const uint32 size ) noexcept {
    switch ( shape ) {
        case shape::square:
            switch ( size ) {
                case 0:
                    return 1;
                case 1:
                    return 2;
                case 2:
                    return 4;
                case 3:
                    return 8;
                default:
                    return 0;
            }
        case shape::wide:
            switch ( size ) {
                case 0:
                    return 1;
                case 1:
                    return 1;
                case 2:
                    return 2;
                case 3:
                    return 4;
                default:
                    return 0;
            }
        case shape::tall:
            switch ( size ) {
                case 0:
                    return 2;
                case 1:
                    return 4;
                case 2:
                    return 4;
                case 3:
                    return 8;
                default:
                    return 0;
            }
        default:
            return 0;
    }
}

} // object

struct object_regular {
    object::attr0 attr0;
    object::attr1_regular attr1;
    object::attr2 attr2;
    uint16 attr3;
};

struct object_affine {
    object::attr0 attr0;
    object::attr1_affine attr1;
    object::attr2 attr2;
    uint16 attr3;
};

} // gba

#endif // define GBAXX_OBJECT_ATTRIBUTES_HPP
