#ifndef GBAXX_SIO_NORMAL_HPP
#define GBAXX_SIO_NORMAL_HPP

#include <gba/sio/serial_control.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace sio {

struct normal {
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
};

template <>
struct r_control<normal> {
    uint16 sc_value : 1,
            sd_value : 1,
            si_value : 1,
            so_value : 1,
            : 12;
};

static_assert( sizeof( r_control<normal> ) == 2, "r_control<normal> must be tightly packed" );

template <>
struct control<normal> {
    normal::shift_clock shift_clock : 2;
    normal::io_state input_state : 1;
    normal::io_state output_state : 1;
    uint16 : 3;
    bool transferring : 1;
    uint16 : 4;
    normal::transfer_type type : 2;
    bool irq_enable : 1;
};

static_assert( sizeof( control<normal> ) == 2, "control<normal> must be tightly packed" );

} // sio
} // gba

#endif // define GBAXX_SIO_NORMAL_HPP
