#ifndef GBAXX_IO_DISPLAY_HPP
#define GBAXX_IO_DISPLAY_HPP

#include <gba/bit_bool.hpp>
#include <gba/display.hpp>
#include <gba/int.hpp>
#include <gba/io_reg.hpp>

namespace gba {
namespace io {

namespace display {

static reg<gba::display::control>&	control = *reinterpret_cast<reg<gba::display::control> *>( 0x4000000 );
static reg<gba::display::status>&	status = *reinterpret_cast<reg<gba::display::status> *>( 0x4000004 );

static const reg<uint16>&	current_scanline = *reinterpret_cast<const reg<uint16> *>( 0x4000006 );

namespace undocumented {

	static reg<bit_bool<uint16>>&	green_swap = *reinterpret_cast<reg<bit_bool<uint16>> *>( 0x4000002 );

} // undocumented

} // display

} // io
} // gba

#endif // define GBAXX_IO_DISPLAY_HPP