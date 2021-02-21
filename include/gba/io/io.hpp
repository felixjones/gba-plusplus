#ifndef GBAXX_IO_IO_HPP
#define GBAXX_IO_IO_HPP

#include <gba/keypad/keypad_manager.hpp>
#include <gba/registers/keypad_input.hpp>

namespace gba {
namespace io {

using keypad_manager = gba::keypad_manager<reg::keyinput>;

template <unsigned Mode>
struct mode {};

} // io
} // gba

#endif // define GBAXX_IO_IO_HPP
