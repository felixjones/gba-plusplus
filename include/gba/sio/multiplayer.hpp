#ifndef GBAXX_SIO_MULTIPLAYER_HPP
#define GBAXX_SIO_MULTIPLAYER_HPP

#include <gba/sio/serial_control.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace sio {

struct multiplayer {
    enum class baud_rate : uint16 {
        bps_9600 = 0,
        bps_38400 = 1,
        bps_57600 = 2,
        bps_115200 = 3
    };

    enum class input_terminal : bool {
        parent = false,
        child = true
    };

    enum class data_terminal : bool {
        not_ready = false,
        all_ready = true
    };
};

template <>
struct r_control<multiplayer> {
    uint16 sc_value : 1,
            sd_value : 1,
            si_value : 1,
            so_value : 1,
            : 12;
};

static_assert( sizeof( r_control<multiplayer> ) == 2, "r_control<multiplayer> must be tightly packed" );

template <>
struct control<multiplayer> {
    constexpr control() noexcept : baud_rate {}, input_terminal {}, data_terminal {}, player_id {}, error {}, transferring {}, mode { 0x2 }, irq_enable {} {}

    multiplayer::baud_rate baud_rate : 2;
    multiplayer::input_terminal input_terminal : 1;
    multiplayer::data_terminal data_terminal : 1;
    uint16 player_id : 2;
    bool error : 1,
            transferring : 1;
    uint16 : 4;
    const uint16 mode : 2;
    bool irq_enable : 1;
};

static_assert( sizeof( control<multiplayer> ) == 2, "control<multiplayer> must be tightly packed" );

} // sio
} // gba

#endif // define GBAXX_SIO_MULTIPLAYER_HPP
