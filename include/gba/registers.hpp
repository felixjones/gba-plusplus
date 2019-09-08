#ifndef GBAXX_REGISTERS_HPP
#define GBAXX_REGISTERS_HPP

#include <gba/display.hpp>

namespace gba {
namespace io {

template <class Register>
constexpr volatile Register& registers() {
	throw "Unimplemented register";
}

template <>
volatile display::control& registers<display::control>() {
	return *reinterpret_cast<volatile display::control *>( 0x4000000 );
}

template <>
volatile display::status& registers<display::status>() {
	return *reinterpret_cast< volatile display::status * >( 0x4000004 );
}

template <>
volatile display::vertical_counter& registers<display::vertical_counter>() {
	return *reinterpret_cast< volatile display::vertical_counter * >( 0x4000006 );
}

} // io
} // gba

#endif // define GBAXX_REGISTERS_HPP
