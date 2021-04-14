#ifndef GBAXX_SOUND_DMG_CHANNEL1_HPP
#define GBAXX_SOUND_DMG_CHANNEL1_HPP

#include <algorithm>

#include <gba/types/int_type.hpp>

namespace gba {
namespace sound {
namespace dmg {

enum class direction : bool {
    increase = false,
    decrease = true,

    increment = false,
    decrement = true,

    up = false,
    down = true
};

enum class period : uint8 {
    off = 0,

    khz_1_128 = 1,
    khz_2_128 = 2,
    khz_3_128 = 3,
    khz_4_128 = 4,
    khz_5_128 = 5,
    khz_6_128 = 6,
    khz_7_128 = 7,

    ms_7_8125 = 1,
    ms_15_625 = 2,
    ms_23_4375 = 3,
    ms_31_25 = 4,
    ms_39_0625 = 5,
    ms_46_875 = 6,
    ms_54_6875 = 7
};

struct channel1_0 {
    uint8 shifts : 3;
    dmg::direction direction : 1;
    dmg::period period : 3;
    uint8 : 1;
};

static_assert( sizeof( channel1_0 ) == 1, "channel1_0 must be tightly packed" );

enum class wave_duty_cycle : uint8 {
    _1_8 = 0,
    _2_8 = 1,
    _4_8 = 2,
    _6_8 = 3,

    _1_4 = 1,
    _2_4 = 2,
    _3_4 = 3,

    _1_2 = 2,

    eighth = 0,
    quarter = 1,
    half = 2,
    three_quarters = 3
};

struct channel1_1 {
    template <unsigned Millis>
    static constexpr uint8 millis_to_length() noexcept {
        return uint8( 64 ) - uint8( ( 256.0L * Millis / 1000.0L + 0.5L ) );
    }

    uint8 length : 6;
    dmg::wave_duty_cycle wave_duty_cycle : 2;
};

} // dmg
} // sound
} // gba

#endif // define GBAXX_SOUND_DMG_CHANNEL1_HPP
