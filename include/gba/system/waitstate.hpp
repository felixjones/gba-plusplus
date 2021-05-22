#ifndef GBAXX_SYSTEM_WAITSTATE_HPP
#define GBAXX_SYSTEM_WAITSTATE_HPP

#include <gba/types/int_type.hpp>

namespace gba {
namespace waitstate {

enum class delay : uint32 {
    cycles_4 = 0,
    cycles_3 = 1,
    cycles_2 = 2,
    cycles_8 = 3
};

enum class delay_sequential : bool {
    cycles_2 = false,
    cycles_1 = true
};

enum class phi_terminal_output : uint32 {
    disabled = 0,
    mHz_4_19 = 1,
    mHz_8_38 = 2,
    mHz_16_78 = 3
};

enum class game_pak_type : bool {
    agb = false,
    cgb = true,

    advance_game_boy = agb,
    color_game_boy = cgb
};

struct control {
    delay game_pak_ram : 2;
    delay state0 : 2;
    delay_sequential state0_sequential : 1;
    delay state1 : 2;
    delay_sequential state1_sequential : 1;
    delay state2 : 2;
    delay_sequential state2_sequential : 1;
    waitstate::phi_terminal_output phi_terminal_output : 2;
    uint32 : 1;
    bool use_game_pak_prefetch : 1;
    const waitstate::game_pak_type game_pak_type : 1;
    uint32 : 16;
};

static_assert( sizeof( control ) == 4, "control must be tightly packed" );

} // waitstate
} // gba

#endif // define GBAXX_SYSTEM_WAITSTATE_HPP
