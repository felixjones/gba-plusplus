#ifndef GBAXX_IO_REGISTERS_HPP
#define GBAXX_IO_REGISTERS_HPP

#include <gba/video/display_control.hpp>
#include <gba/video/display_status.hpp>

namespace gba {
namespace io {

using display_control = gba::iomemmap<gba::display_control, 0x4000000>;
using display_status = gba::iomemmap<gba::display_status, 0x4000004>;
using vertical_count = gba::imemmap<uint16, 0x4000006>;

} // io
} // gba

#endif // define GBAXX_IO_REGISTERS_HPP
