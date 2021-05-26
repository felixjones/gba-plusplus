#ifndef GBAXX_BIOS_AFFINE_HPP
#define GBAXX_BIOS_AFFINE_HPP

#include <gba/bios/swi.hpp>
#include <gba/object/attributes.hpp>
#include <gba/types/fixed_point.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace bios {

struct alignas( uint32 ) bg_affine_input {
    make_fixed<23, 8> origin_x;
    make_fixed<23, 8> origin_y;
    make_fixed<7, 8> display_x;
    make_fixed<7, 8> display_y;
    make_fixed<7, 8> scale_x;
    make_fixed<7, 8> scale_y;
    make_ufixed<8, 8> rotation;
};

static_assert( sizeof( bg_affine_input ) == 20, "bg_affine_input must be 4 byte aligned" );

struct alignas( uint32 ) bg_affine_output {
    int16 same_x;
    int16 next_x;
    int16 same_y;
    int16 next_y;
    int32 start_x;
    int32 start_y;
};

static_assert( sizeof( bg_affine_output ) == 16, "bg_affine_output must be 4 byte aligned" );

[[gnu::always_inline]]
inline void bg_affine_set( const bg_affine_input * input, bg_affine_output * output, unsigned int count ) noexcept {
    swi<0xe, void( const void *, void *, unsigned int )>::call( input, output, count );
}

struct alignas( uint32 ) obj_affine_input {
    make_fixed<7, 8> scale_x;
    make_fixed<7, 8> scale_y;
    make_ufixed<8, 8> rotation;
};

static_assert( sizeof( obj_affine_input ) == 8, "obj_affine_input must be 4 byte aligned" );

[[gnu::always_inline]]
inline void obj_affine_set( const obj_affine_input * input, object::mat2 * output, unsigned int count, unsigned int stride ) noexcept {
    swi<15, void( const void *, void *, unsigned int, unsigned int )>::call( input, output, count, stride );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_AFFINE_HPP
