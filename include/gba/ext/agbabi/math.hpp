#ifndef GBAXX_EXT_AGBABI_MATH_HPP
#define GBAXX_EXT_AGBABI_MATH_HPP

#if defined( __agb_abi )

#include <tuple>

#include <gba/types/fixed_point.hpp>
#include <gba/types/int_type.hpp>

extern "C" {

unsigned long long __agbabi_unsafe_uidiv( unsigned numerator, unsigned denominator );
int __agbabi_sin( int x );

}

namespace gba {
namespace agbabi {

std::tuple<uint32, uint32> unsafe_uidiv( uint32 numerator, uint32 denominator ) noexcept {
    asm(
    ".extern\t__agbabi_unsafe_uidiv\n\t"
#if defined( __thumb__ )
    "movs\tr0, %[r0]\n\t"
    "movs\tr1, %[r1]\n\t"
    "bl\t__agbabi_unsafe_uidiv\n\t"
    "movs\t%[r0], r0\n\t"
    "movs\t%[r1], r1"
#elif defined( __arm__ )
    "mov\tr0, %[r0]\n\t"
    "mov\tr1, %[r1]\n\t"
    "bl\t__agbabi_unsafe_uidiv\n\t"
    "mov\t%[r0], r0\n\t"
    "mov\t%[r1], r1"
#endif
    : [r0]"+r"( numerator ), [r1]"+r"( denominator )
    :: "r0", "r1", "r2", "r3"
    );
    return std::make_tuple( numerator, denominator );
}

auto sin( int bam16 ) noexcept {
    return make_fixed<2, 29>::from_data( __agbabi_sin( bam16 ) );
}

} // agbabi
} // gba

#endif // __agb_abi

#endif // define GBAXX_EXT_AGBABI_MATH_HPP
