#ifndef GBAXX_BIOS_HALT_HPP
#define GBAXX_BIOS_HALT_HPP

#include <gba/bios/swi.hpp>
#include <gba/types/int_cast.hpp>
#include <gba/types/interrupt_mask.hpp>

namespace gba {
namespace bios {

[[gnu::always_inline]]
inline void halt() noexcept {
    swi<2, void()>::call();
}

[[gnu::always_inline]]
inline void stop() noexcept {
    swi<3, void()>::call();
}

[[gnu::always_inline]]
inline void intr_wait( bool resetFlag, interrupt_mask flags ) noexcept {
    swi<4, void( int, int )>::call( resetFlag, int_cast( flags ) );
}

[[gnu::always_inline]]
inline void vblank_intr_wait() noexcept {
    swi<5, void( void )>::call();
}

namespace undocumented {

[[gnu::always_inline]]
inline void custom_halt( bool stop ) noexcept {
    swi<0x27, void( int )>::call_2( stop ? 0x80 : 0 );
}

} // undocumented
} // bios
} // gba

#endif // define GBAXX_BIOS_HALT_HPP
