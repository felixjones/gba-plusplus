#ifndef GBAXX_BIOS_RESET_HPP
#define GBAXX_BIOS_RESET_HPP

#include <gba/bios/swi.hpp>
#include <gba/types/bit_container.hpp>

namespace gba {
namespace bios {

[[noreturn, gnu::always_inline]]
inline void soft_reset() noexcept {
    swi<0, void()>::call();
    __builtin_unreachable();
}

struct reset_flags {
    bool ewram : 1,
        iwram : 1,
        palette : 1,
        vram : 1,
        oam : 1,
        reg_sio : 1,
        reg_sound : 1,
        reg : 1;
};

[[gnu::always_inline]]
inline void register_ram_reset( reset_flags flags ) noexcept {
    swi<1, void( int )>::call( to_bit_container( flags ) );
}

namespace undocumented {

[[noreturn, gnu::always_inline]]
inline void hard_reset() noexcept {
    swi<0x26, void()>::call();
    __builtin_unreachable();
}

} // undocumented
} // bios
} // gba

#endif // define GBAXX_BIOS_RESET_HPP
