#ifndef GBAXX_BIOS_AFFINE_HPP
#define GBAXX_BIOS_AFFINE_HPP

#include <gba/bios/swi.hpp>
#include <gba/types/fixed_point.hpp>
#include <gba/types/matrix/mat2x2.hpp>

namespace gba {
namespace bios {

struct alignas( 8 ) obj_affine_input {
    fixed_point<int16, -8> scale_x;
    fixed_point<int16, -8> scale_y;
    fixed_point<uint16, -8> rotation;
};

static_assert( sizeof( obj_affine_input ) == 8, "obj_affine_input must be 4 byte aligned" );

struct obj_affine_matrix {
    fixed_point<int16, -8> pa;
    fixed_point<int16, -8> pb;
    fixed_point<int16, -8> pc;
    fixed_point<int16, -8> pd;
};

static_assert( sizeof( obj_affine_matrix ) == 8, "obj_affine_matrix must be tightly packed" );

[[gnu::always_inline]]
inline void obj_affine_set( const obj_affine_input * input, obj_affine_matrix * output, unsigned int count, unsigned int stride ) noexcept {
    swi<15, void( const void *, void *, unsigned int, unsigned int )>::call( input, output, count, stride );
}

[[gnu::always_inline]]
inline void obj_affine_set( const obj_affine_input * input, mat2<fixed_point<int16, -8>> * output, unsigned int count, unsigned int stride ) noexcept {
    swi<15, void( const void *, void *, unsigned int, unsigned int )>::call( input, output, count, stride );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_AFFINE_HPP
