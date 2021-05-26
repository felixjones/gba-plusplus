#ifndef GBAXX_BIOS_SYSTEM_HPP
#define GBAXX_BIOS_SYSTEM_HPP

#include <gba/bios/swi.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace bios {
namespace undocumented {

[[nodiscard, gnu::always_inline, gnu::const]]
inline uint32 get_bios_checksum() noexcept {
    return swi<0x0d, unsigned( void )>::call();
}

} // undocumented

enum class multi_boot_mode : int {
    normal_32bit_256_KHz = 0,
    multi_play_16bit_115_KHz = 1,
    normal_32bit_2_MHz = 2
};

enum class multi_boot_status : int {
    okay = 0,
    failed = 1,

    error = failed
};

struct [[gnu::packed]] multi_boot_param {
    uint32 _0[3];
    uint16 _1;
    uint8 handshake_data;
    uint32 _2;
    uint8 client_data[3];
    uint8 palette_data;
    uint8 _3;
    uint8 client_bit;
    uint8 _4;
    uint32 boot_srcp;
    uint32 boot_endp;
};

static_assert( sizeof( multi_boot_param ) == 0x22, "multi_boot_param must be tightly packed" );

[[nodiscard, gnu::always_inline]]
inline multi_boot_status multi_boot( const multi_boot_param * param, const multi_boot_mode mode ) noexcept {
    const auto status = swi<0x25, int( const void *, int )>::call( param, int( mode ) );
    return multi_boot_status( status );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_SYSTEM_HPP
