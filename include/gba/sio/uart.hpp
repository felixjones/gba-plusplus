#ifndef GBAXX_SIO_UART_HPP
#define GBAXX_SIO_UART_HPP

#include <gba/sio/serial_control.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace sio {

struct uart {
    enum class baud_rate : uint16 {
        bps_9600 = 0,
        bps_38400 = 1,
        bps_57600 = 2,
        bps_115200 = 3
    };

    enum class clear_to_send : bool {
        always = false,
        when_sc_low = true
    };

    enum class parity : bool {
        even = false,
        odd = true
    };


    enum class data_length : bool {
        bits_7 = false,
        bits_8 = true
    };
};

template <>
struct r_control<uart> {
    uint16 sc_value : 1,
            sd_value : 1,
            si_value : 1,
            so_value : 1,
            : 12;
};

static_assert( sizeof( r_control<uart> ) == 2, "r_control<uart> must be tightly packed" );

template <>
struct control<uart> {
    constexpr control() noexcept : baud_rate {}, clear_to_send {}, parity {}, send_data {}, receive_data {}, error {}, data_length {}, fifo_enable {}, parity_enable {}, send_enable {},
        receive_enable {}, mode { 0x3 }, irq_enable {} {}

    uart::baud_rate baud_rate : 2;
    uart::clear_to_send clear_to_send : 1;
    uart::parity parity : 1;
    bool send_data : 1,
        receive_data : 1,
        error : 1;
    uart::data_length data_length : 1;
    bool fifo_enable : 1,
        parity_enable : 1,
        send_enable : 1,
        receive_enable : 1;
    const uint16 mode : 2;
    bool irq_enable : 1;
};

static_assert( sizeof( control<uart> ) == 2, "control<uart> must be tightly packed" );

} // sio
} // gba

#endif // define GBAXX_SIO_UART_HPP
