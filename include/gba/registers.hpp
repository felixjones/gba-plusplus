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

} // io
} // gba

#endif // define GBAXX_REGISTERS_HPP
