#ifndef GBAXX_EXT_MGBA_HPP
#define GBAXX_EXT_MGBA_HPP

#include <gba/types/memmap.hpp>

namespace gba {
namespace mgba {

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

} // mgba
} // gba

#endif // define GBAXX_EXT_MGBA_HPP
