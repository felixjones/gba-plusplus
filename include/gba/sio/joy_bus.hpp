#ifndef GBAXX_SIO_JOY_BUS_HPP
#define GBAXX_SIO_JOY_BUS_HPP

#include <gba/sio/serial_control.hpp>
#include <gba/types/int_type.hpp>

namespace gba {

struct joy_bus {
    struct control {
        bool device_reset : 1,
            receive_complete : 1,
            send_complete : 1,
            : 3,
            irq_enable : 1;
        uint32 : 25;
    };

    static_assert( sizeof( control ) == 4, "control must be tightly packed" );

    struct status {
        uint32 : 1;
        const bool transfer_okay : 1;
        uint32 : 1;
        const bool receive_okay : 1;
        uint32 general_purpose_data : 2;
        uint32 : 26;
    };

    static_assert( sizeof( status ) == 4, "status must be tightly packed" );
};

namespace sio {

template <>
struct r_control<joy_bus> {
    constexpr r_control() noexcept : sc_value {}, sd_value {}, si_value {}, so_value {}, serial_mode { 0x3 } {}

    uint16 sc_value : 1,
            sd_value : 1,
            si_value : 1,
            so_value : 1,
            : 10;
    const uint16 serial_mode : 2;
};

static_assert( sizeof( r_control<joy_bus> ) == 2, "r_control<joy_bus> must be tightly packed" );

} // sio
} // gba

#endif // define GBAXX_SIO_JOY_BUS_HPP
