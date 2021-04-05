#ifndef GBAXX_BIOS_AFFINE_HPP
#define GBAXX_BIOS_AFFINE_HPP

#include <gba/bios/swi.hpp>
#include <gba/object/attributes.hpp>
#include <gba/types/fixed_point.hpp>

namespace gba {
namespace bios {

struct alignas( 4 ) obj_affine_input {
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
