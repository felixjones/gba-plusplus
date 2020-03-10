#ifndef GBAXX_GBA_HPP
#define GBAXX_GBA_HPP

#include <gba/bios.hpp>
#include <gba/bool.hpp>
#include <gba/display_control.hpp>
#include <gba/display_status.hpp>
#include <gba/fixed_point.hpp>
#include <gba/int.hpp>
#include <gba/int_type.hpp>
#include <gba/interrupt.hpp>
#include <gba/interrupt_handler.hpp>
#include <gba/math.hpp>
#include <gba/memmap.hpp>
#include <gba/sized_bool.hpp>

namespace gba {
namespace io {
	using display_control = iomemmap<gba::display_control, 0x04000000>;
	using display_status = iomemmap<gba::display_status, 0x04000004>;
	using vertical_counter = imemmap<gba::uint16, 0x04000006>;

	using interrupt_master_enable = iomemmap<gba::bool32, 0x04000208>;
	using interrupt_mask_enable = iomemmap<gba::interrupt, 0x4000200>;
	using interrupt_flags = iomemmap<gba::interrupt, 0x4000202>;
} // io

namespace undocumented {
namespace io {
	using display_control_green_swap = iomemmap<bool16, 0x04000002>;
} // io
} // undocumented
} // gba

#endif // define GBAXX_GBA_HPP
