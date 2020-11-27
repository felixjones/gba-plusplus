#ifndef GBAXX_IO_REGISTERS_HPP
#define GBAXX_IO_REGISTERS_HPP

#include <gba/video/display_control.hpp>

namespace gba {
namespace io {

static_assert( sizeof( gba::display_control ) == 2, "sizeof display_control must be 2" );
using display_control = gba::iomemmap<gba::display_control, 0x4000000>;

} // io
} // gba

#endif // define GBAXX_IO_REGISTERS_HPP
