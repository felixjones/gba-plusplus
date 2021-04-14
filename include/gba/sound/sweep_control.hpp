#ifndef GBAXX_SOUND_SWEEP_CONTROL_HPP
#define GBAXX_SOUND_SWEEP_CONTROL_HPP

namespace gba {
namespace sound {

namespace shift {

    enum class direction : bool {
        increase = false,
        decrease = true
    };

    enum class delay : uint16 {
        off = 0,

        _1_128khz = 1,
        _2_128khz = 2,
        _3_128khz = 3,
        _4_128khz = 4,
        _5_128khz = 5,
        _6_128khz = 6,
        _7_128khz = 7,

        ms_7_8125 = 1,
        ms_15_625 = 2,
        ms_23_4375 = 3,
        ms_31_25 = 4,
        ms_39_0625 = 5,
        ms_46_875 = 6,
        ms_54_6875 = 7
    };

} // shift

struct sweep_control {
    uint16 shift_count : 3;
    shift::direction shift_direction : 1;
    shift::delay shift_delay : 3;
};

static_assert( sizeof( sweep_control ) == 2, "sweep_control must be tightly packed" );

} // sound
} // gba

#endif // define GBAXX_SOUND_SWEEP_CONTROL_HPP
