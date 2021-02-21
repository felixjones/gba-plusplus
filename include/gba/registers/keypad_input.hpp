#ifndef GBAXX_REGISTERS_KEYPAD_INPUT_HPP
#define GBAXX_REGISTERS_KEYPAD_INPUT_HPP

#include <gba/keypad/keypad.hpp>
#include <gba/types/memmap.hpp>

namespace gba {
namespace reg {

using keyinput = imemmap<keypad, 0x4000130>;

} // reg
} // gba

#endif // define GBAXX_REGISTERS_KEYPAD_INPUT_HPP
