#ifndef GBAXX_BIOS_SOUND_HPP
#define GBAXX_BIOS_SOUND_HPP

#include <gba/bios/swi.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace bios {

struct wave_data_header {
    uint16 type;
    uint16 stat;
    uint32 freq;
    uint32 loop;
    uint32 size;
};

static_assert( sizeof( wave_data_header ) == 16, "wave_data_header must be tightly packed" );

[[nodiscard, gnu::always_inline]]
inline uint32 midi_key_2_freq( const wave_data_header * wa, uint8 mk, uint8 fp ) noexcept {
    return swi<0x1f, unsigned int( const void *, unsigned char, unsigned char )>::call( wa, mk, fp );
}

[[gnu::always_inline]]
inline void sound_bias( int level ) noexcept {
    swi<0x19, void( int )>::call( level );
}

[[gnu::always_inline]]
inline void sound_channel_clear() noexcept {
    swi<0x1e, void( void )>::call();
}

} // bios
} // gba

#endif // define GBAXX_BIOS_SOUND_HPP
