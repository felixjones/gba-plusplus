#ifndef GBAXX_BIOS_SQRT_HPP
#define GBAXX_BIOS_SQRT_HPP

#include <tuple>

#include <gba/bios/swi.hpp>

namespace gba {
namespace bios {

[[nodiscard, gnu::always_inline, gnu::pure]]
inline auto div( int number, int denom ) noexcept {
    return swi<6, std::tuple<int, int, unsigned int>( int, int )>::call( number, denom );
}

[[nodiscard, gnu::always_inline, gnu::pure]]
inline auto sqrt( unsigned int x ) noexcept {
    return swi<8, unsigned int( unsigned int )>::call( x );
}

[[nodiscard, gnu::always_inline, gnu::pure]]
inline auto arc_tan2( short x, short y ) noexcept {
    return swi<0xa, short( short, short )>::call( x, y );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_SQRT_HPP
