#ifndef GBAXX_VIDEO_OBJECT_ATTRIBUTE_HPP
#define GBAXX_VIDEO_OBJECT_ATTRIBUTE_HPP

namespace gba {
namespace object {

    enum class graphics_mode : uint16 {
        normal = 0,
        blended = 1,
        windowed = 2
    };

    enum class color_mode : uint16 {
        bpp4 = 0,
        bpp8 = 1
    };

    enum class shape : uint16 {
        square = 0,
        wide = 1,
        tall = 2
    };

} // object

struct [[gnu::aligned( 4 )]] object_regular {
    uint16 y : 8;
    bool : 1; // false
    bool visible : 1;
    object::graphics_mode graphics : 2;
    bool mosaic : 1;
    object::color_mode color : 1;
    object::shape shape : 2;

    uint16 x : 12;
    bool flip_x : 1, flip_y : 1;
    uint16 size : 2;

    uint16 tile_index : 10;
    uint16 priority : 2;
    uint16 palette_bank : 4;
};

static_assert( sizeof( object_regular ) == 8, "object_affine must be aligned 4" );

struct [[gnu::aligned( 4 )]] object_affine {
    uint16 y : 8;
    bool : 1; // true
    bool double_size : 1;
    object::graphics_mode graphics : 2;
    bool mosaic : 1;
    object::color_mode color : 1;
    object::shape shape : 2;

    uint16 x : 9;
    uint16 affine_index : 5;
    uint16 size : 2;

    uint16 tile_index : 10;
    uint16 priority : 2;
    uint16 palette_bank : 4;
};

static_assert( sizeof( object_affine ) == 8, "object_affine must be aligned 4" );

using object_attributes_regular = bufmap<0x7000000, object_regular, 128>;
using object_attributes_affine = bufmap<0x7000000, object_affine, 128>;

} // gba

#endif // define GBAXX_VIDEO_OBJECT_ATTRIBUTE_HPP
