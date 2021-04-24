#ifndef GBAXX_SOUND_DIRECT_HPP
#define GBAXX_SOUND_DIRECT_HPP

#include <gba/types/int_type.hpp>

namespace gba {
namespace sound {

enum class dmg_volume : uint16 {
    quarter = 0,
    half = 1,
    full = 2
};

enum class directsound_volume : uint16 {
    half = 0,
    full = 1
};

struct directsound_control {
    sound::dmg_volume dmg_volume : 2;
    directsound_volume volume_soundA : 1;
    directsound_volume volume_soundB : 1;
    uint16 : 4;
    bool enable_soundA_right : 1,
        enable_soundA_left : 1;
    uint16 timer_soundA : 1;
    bool reset_soundA : 1;
    bool enable_soundB_right : 1,
        enable_soundB_left : 1;
    uint16 timer_soundB : 1;
    bool reset_soundB : 1;
};

static_assert( sizeof( directsound_control ) == 2, "directsound_control must be tightly packed" );

} // sound
} // gba

#endif // define GBAXX_SOUND_DIRECT_HPP
