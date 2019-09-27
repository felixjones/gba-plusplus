#ifndef GBAXX_IO_KEYPAD_HPP
#define GBAXX_IO_KEYPAD_HPP

#include <gba/int.hpp>
#include <gba/io_reg.hpp>
#include <gba/keypad.hpp>

namespace gba {
namespace io {

namespace keypad {

static const reg<gba::keypad::input>& input = *reinterpret_cast<const reg<gba::keypad::input> *>( 0x4000130 );
static reg<gba::keypad::irq_control>& irq_control = *reinterpret_cast<reg<gba::keypad::irq_control> *>( 0x4000132 );

} // keypad

} // io
} // gba

#endif // define GBAXX_IO_KEYPAD_HPP