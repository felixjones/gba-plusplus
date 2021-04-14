#ifndef GBAXX_SOUND_FREQUENCY_CONTROL_HPP
#define GBAXX_SOUND_FREQUENCY_CONTROL_HPP

namespace gba {
namespace sound {

struct frequency {
    uint32 freq : 11,
        : 3;
    bool length : 1,
        restart : 1;
    uint32 : 16;
};

} // sound
} // gba

#endif // define GBAXX_SOUND_FREQUENCY_CONTROL_HPP
