#ifndef GBAXX_BIOS_CPU_COPY_HPP
#define GBAXX_BIOS_CPU_COPY_HPP

#include <tuple>

#include <gba/bios/swi.hpp>
#include <gba/types/int_cast.hpp>
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
    swi<12, void( const void *, void *, unsigned int )>::call( src, dst, uint_cast( mode ) );
}

struct transfer {
    enum class type {
        half = 0,
        word = 1
    };

    uint32 transfers : 21, : 3;
    bool fill : 1, : 1;
    transfer::type type : 1;
};

static_assert( sizeof( transfer ) == 4, "transfer must be tightly packed" );

[[gnu::always_inline]]
inline void cpu_set( const void * src, void * dst, transfer mode ) noexcept {
    swi<11, void( const void *, void *, unsigned int )>::call( src, dst, uint_cast( mode ) );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_CPU_COPY_HPP
