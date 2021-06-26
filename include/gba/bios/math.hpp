#ifndef GBAXX_BIOS_SQRT_HPP
#define GBAXX_BIOS_SQRT_HPP

#include <tuple>

#include <gba/bios/swi.hpp>

namespace gba {
namespace bios {

[[nodiscard, gnu::always_inline, gnu::const]]
inline auto div( int number, int denom ) noexcept {
    return swi<6, std::tuple<int, int, unsigned int>( int, int )>::call( number, denom );
}

[[nodiscard, gnu::always_inline, gnu::const]]
inline auto div_arm( int denom, int number ) noexcept {
    return swi<7, std::tuple<int, int, unsigned int>( int, int )>::call( denom, number );
}

[[nodiscard, gnu::always_inline, gnu::const]]
inline auto sqrt( unsigned int x ) noexcept {
    return swi<8, unsigned int( unsigned int )>::call( x );
}

[[nodiscard, gnu::always_inline, gnu::const]]
inline auto arc_tan( short x ) noexcept {
    return swi<0x9, short( short )>::call( x );
}

[[nodiscard, gnu::always_inline, gnu::const]]
inline auto arc_tan2( int x, int y ) noexcept {
    return swi<0xa, int( int, int )>::call( x, y );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_SQRT_HPP
