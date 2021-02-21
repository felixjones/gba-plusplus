#ifndef GBAXX_REGISTERS_DISPLAY_HPP
#define GBAXX_REGISTERS_DISPLAY_HPP

#include <gba/display/display_control.hpp>
#include <gba/display/interrupt_status.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/memmap.hpp>

namespace gba {
namespace reg {

using dispcnt = iomemmap<display_control, 0x4000000>;
using dispstat = iomemmap<display_status, 0x4000004>;
using vcount = imemmap<uint16, 0x4000006>;

} // reg
} // gba

#endif // define GBAXX_REGISTERS_DISPLAY_HPP
