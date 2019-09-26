#ifndef GBAXX_IO_KEYPAD_HPP
#define GBAXX_IO_KEYPAD_HPP

#include <gba/io_reg.hpp>
#include <gba/keypad.hpp>

namespace gba {
namespace io {

namespace keypad {

static const reg<gba::keypad::bits>& input = *reinterpret_cast<const reg<gba::keypad::bits> *>( 0x4000130 );
static reg<gba::keypad::bits>& irq_control = *reinterpret_cast<reg<gba::keypad::bits> *>( 0x4000132 );

} // keypad

} // io
} // gba

#endif // define GBAXX_IO_KEYPAD_HPP