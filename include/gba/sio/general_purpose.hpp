#ifndef GBAXX_SIO_GENERAL_PURPOSE_HPP
#define GBAXX_SIO_GENERAL_PURPOSE_HPP

#include <gba/sio/serial_control.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace sio {

struct general {
    enum class direction : bool {
        input = false,
        output = true,

        in = input,
        out = output
    };
};

template <>
struct r_control<general> {
    constexpr r_control() noexcept : sc_value {}, sd_value {}, si_value {}, so_value {}, sc_direction {}, sd_direction {}, si_direction {}, so_direction {}, si_irq_enable {}, serial_mode { 0x2 } {}

    uint16 sc_value : 1,
        sd_value : 1,
        si_value : 1,
        so_value : 1;
    general::direction sc_direction : 1,
        sd_direction : 1,
        si_direction : 1,
        so_direction : 1;
    bool si_irq_enable : 1;
    uint16 : 5;
    const uint16 serial_mode : 2;
};

static_assert( sizeof( r_control<general> ) == 2, "r_control<general> must be tightly packed" );

} // sio
} // gba

#endif // define GBAXX_SIO_GENERAL_PURPOSE_HPP
