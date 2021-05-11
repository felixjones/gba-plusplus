#ifndef GBAXX_COMMS_SIO_CONTROL_HPP
#define GBAXX_COMMS_SIO_CONTROL_HPP

#include <gba/types/int_type.hpp>

namespace gba {
namespace sio {

    struct normal {};

    template <class Mode>
    struct r_control {};

    template <>
    struct r_control<normal> {
        const uint16 zero = 0;
    };

    static_assert( sizeof( r_control<normal> ) == 2, "r_control<normal> must be tightly packed" );

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

    enum class transfer_type : bool {
        half = false,
        word = true
    };

    template <class Mode>
    struct control {};

    template <>
    struct control<normal> {
        sio::shift_clock shift_clock : 2;
        const io_state input_state : 1;
        io_state output_state : 1;
        uint16 : 3;
        bool transferring : 1;
        uint16 : 4;
        transfer_type type : 1;
        uint16 : 1;
        bool irq_enable : 1;
    };

    static_assert( sizeof( control<normal> ) == 2, "control<normal> must be tightly packed" );

} // sio
} // gba

#endif // define GBAXX_COMMS_SIO_CONTROL_HPP
