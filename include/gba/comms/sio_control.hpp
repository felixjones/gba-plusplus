#ifndef GBAXX_COMMS_SIO_CONTROL_HPP
#define GBAXX_COMMS_SIO_CONTROL_HPP

#include <gba/types/int_type.hpp>

namespace gba {
namespace sio {

    struct normal {};
    struct multiplayer {};

    template <class Mode>
    struct r_control {};

    template <>
    struct r_control<normal> {
        const uint16 zero = 0;
    };

    static_assert( sizeof( r_control<normal> ) == 2, "r_control<normal> must be tightly packed" );

    template <>
    struct r_control<multiplayer> {
        const uint16 zero = 0;
    };

    static_assert( sizeof( r_control<multiplayer> ) == 2, "r_control<multiplayer> must be tightly packed" );

    enum class shift_clock : uint16 {
        external = 0,
        internal_256Khz = 1,
        internal_2MHz = 3
    };

    enum class io_state : bool {
        low = false,
        high = true,

        enabled = low,
        disabled = high,

        ready = low,
        not_ready = high
    };

    enum class transfer_type : uint16 {
        byte = 0,
        word = 1
    };

    template <class Mode>
    struct control {};

    template <>
    struct control<normal> {
        sio::shift_clock shift_clock : 2;
        io_state input_state : 1;
        io_state output_state : 1;
        uint16 : 3;
        bool transferring : 1;
        uint16 : 4;
        transfer_type type : 2;
        bool irq_enable : 1;
    };

    static_assert( sizeof( control<normal> ) == 2, "control<normal> must be tightly packed" );

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

    enum class multiplayer_mode : uint16 {
        value = 2
    };

    template <>
    struct control<multiplayer> {
        sio::baud_rate baud_rate : 2;
        sio::input_terminal input_terminal : 1;
        sio::data_terminal data_terminal : 1;
        uint16 player_id : 2;
        bool error : 1,
            transferring : 1;
        uint16 : 4;
        sio::multiplayer_mode mode : 2;
        bool irq_enable : 1;
    };

    static_assert( sizeof( control<multiplayer> ) == 2, "control<multiplayer> must be tightly packed" );

} // sio
} // gba

#endif // define GBAXX_COMMS_SIO_CONTROL_HPP
