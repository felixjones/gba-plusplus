#ifndef GBAXX_SOUND_SOUND_HPP
#define GBAXX_SOUND_SOUND_HPP

#include <gba/types/int_type.hpp>

namespace gba {
namespace sound {

struct status {
    bool is_playing_square1 : 1,
        is_playing_square2 : 1,
        is_playing_wave : 1,
        is_playing_noise : 1;
    uint16 : 3;
    bool enable_sounds : 1;
};

static_assert( sizeof( status ) == 2, "status must be tightly packed" );

enum class resolution : uint16 {
    bit_9 = 0,
    bit_8 = 1,
    bit_7 = 2,
    bit_6 = 3,

    khz_32_768 = bit_9,
    khz_65_536 = bit_8,
    khz_131_072 = bit_7,
    khz_262_144 = bit_6,
};

struct bias_control {
    uint16 : 1,
        level : 9,
        : 4;
    sound::resolution resolution : 2;
};

static_assert( sizeof( bias_control ) == 2, "bias_control must be tightly packed" );

} // sound
} // gba

#endif // define GBAXX_SOUND_SOUND_HPP
