#ifndef GBAXX_SIO_SERIAL_CONTROL_HPP
#define GBAXX_SIO_SERIAL_CONTROL_HPP

namespace gba {
namespace sio {

template <class Mode>
struct r_control {};

template <class Mode>
struct control {};

} // sio
} // gba

#include <gba/sio/general_purpose.hpp>
#include <gba/sio/joy_bus.hpp>
#include <gba/sio/multiplayer.hpp>
#include <gba/sio/normal.hpp>
#include <gba/sio/uart.hpp>

#endif // define GBAXX_SIO_SERIAL_CONTROL_HPP
