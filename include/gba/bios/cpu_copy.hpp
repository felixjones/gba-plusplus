#ifndef GBAXX_BIOS_CPU_COPY_HPP
#define GBAXX_BIOS_CPU_COPY_HPP

#include <tuple>

#include <gba/bios/swi.hpp>
#include <gba/types/bit_container.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace bios {

struct fast_transfer {
    uint32 transfers : 21, : 3;
    bool fill : 1;
};

static_assert( sizeof( fast_transfer ) == 4, "fast_transfer must be tightly packed" );

[[gnu::always_inline]]
inline void cpu_fast_set( const void * src, void * dst, fast_transfer mode ) noexcept {
    swi<12, void( const void *, void *, unsigned int )>::call( src, dst, to_bit_container( mode ) );
}

enum class transfer_type {
    half = 0,
    word = 1
};

struct transfer {
    uint32 transfers : 21, : 3;
    bool fill : 1, : 1;
    transfer_type type : 1;
};

static_assert( sizeof( transfer ) == 4, "transfer must be tightly packed" );

[[gnu::always_inline]]
inline void cpu_set( const void * src, void * dst, transfer mode ) noexcept {
    swi<11, void( const void *, void *, unsigned int )>::call( src, dst, to_bit_container( mode ) );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_CPU_COPY_HPP
