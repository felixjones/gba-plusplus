#ifndef GBAXX_EXT_MGBA_HPP
#define GBAXX_EXT_MGBA_HPP

#include <gba/types/memmap.hpp>

#if defined( __posprintf )
extern "C" {
#include <posprintf.h>
}
#else
#include <cstdio>
#endif

namespace gba {
namespace mgba {

enum class debug_level : int {
    fatal = 0,
    error = 1,
    warn = 2,
    info = 3,
    debug = 4
};

namespace reg {

using debug_enable = iomemmap<uint16, 0x4fff780>;
using debug_flags = omemmap<uint16, 0x4fff700>;

} // reg

[[gnu::always_inline]]
inline bool open() noexcept {
    reg::debug_enable::write( 0xc0de );
    return reg::debug_enable::read() == 0x1dea;
}

[[gnu::always_inline]]
inline void close() noexcept {
    reg::debug_enable::write( 0 );
}

template <typename ...Args>
inline void printf( const debug_level lvl, const char * fmt, Args... args ) noexcept {
    char * const address = reinterpret_cast<char *>( 0x4fff600 );
#if defined( __posprintf )
    posprintf( address, fmt, args... );
#else
    std::vsnprintf( address, 0x100, fmt, args... );
#endif
    reg::debug_flags::write( static_cast<uint16>( lvl ) | 0x100 );
}

} // mgba
} // gba

#endif // define GBAXX_EXT_MGBA_HPP
