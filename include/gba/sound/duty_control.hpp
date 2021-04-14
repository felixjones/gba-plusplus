#ifndef GBAXX_SOUND_DUTY_CONTROL_HPP
#define GBAXX_SOUND_DUTY_CONTROL_HPP

namespace gba {
namespace sound {

namespace wave {

enum class duty : uint16 {
    eighth = 0,
    quarter = 1,
    half = 2,
    three_quarters = 3,

    _12_5 = 0,
    _25 = 1,
    _50 = 2,
    _75 = 3
};

} // wave


struct duty_control {
    uint16 length : 6;
    wave::duty duty : 2;
    uint16 step_time : 3;
    bool increase : 1;
    uint16 start_volume : 4;
};

} // sound
} // gba

#endif // define GBAXX_SOUND_DUTY_CONTROL_HPP
