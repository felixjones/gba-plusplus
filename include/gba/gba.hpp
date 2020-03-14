#ifndef GBAXX_GBA_HPP
#define GBAXX_GBA_HPP

#include <gba/background_control.hpp>
#include <gba/bios.hpp>
#include <gba/bool.hpp>
#include <gba/const.hpp>
#include <gba/display_control.hpp>
#include <gba/display_status.hpp>
#include <gba/fixed_point.hpp>
#include <gba/int.hpp>
#include <gba/int_type.hpp>
#include <gba/interrupt.hpp>
#include <gba/interrupt_handler.hpp>
#include <gba/mat2.hpp>
#include <gba/math.hpp>
#include <gba/memmap.hpp>
#include <gba/sized_bool.hpp>
#include <gba/vec2.hpp>
#include <gba/vec3.hpp>

namespace gba {
namespace io {
	using display_control = iomemmap<gba::display_control, 0x04000000>;

	using display_status = iomemmap<gba::display_status, 0x04000004>;
	using vertical_counter = imemmap<gba::uint16, 0x04000006>;

	using background0_control = iomemmap<gba::display_control, 0x04000008>;
	using background1_control = iomemmap<gba::display_control, 0x0400000A>;
	using background2_control = iomemmap<gba::display_control, 0x0400000C>;
	using background3_control = iomemmap<gba::display_control, 0x0400000E>;

	using background0_scroll = omemmap<gba::vec2<gba::int16>, 0x04000010>;
	using background1_scroll = omemmap<gba::vec2<gba::int16>, 0x04000014>;
	using background2_scroll = omemmap<gba::vec2<gba::int16>, 0x04000018>;
	using background3_scroll = omemmap<gba::vec2<gba::int16>, 0x0400001C>;

	using background2_a = omemmap<gba::make_fixed<8, 8>, 0x04000020>;
	using background2_b = omemmap<gba::make_fixed<8, 8>, 0x04000022>;
	using background2_c = omemmap<gba::make_fixed<8, 8>, 0x04000024>;
	using background2_d = omemmap<gba::make_fixed<8, 8>, 0x04000026>;
	using background2_x = omemmap<gba::make_fixed<20, 8>, 0x04000028>;
	using background2_y = omemmap<gba::make_fixed<20, 8>, 0x0400002C>;

	using background3_a = omemmap<gba::make_fixed<8, 8>, 0x04000030>;
	using background3_b = omemmap<gba::make_fixed<8, 8>, 0x04000032>;
	using background3_c = omemmap<gba::make_fixed<8, 8>, 0x04000034>;
	using background3_d = omemmap<gba::make_fixed<8, 8>, 0x04000036>;
	using background3_x = omemmap<gba::make_fixed<20, 8>, 0x04000038>;
	using background3_y = omemmap<gba::make_fixed<20, 8>, 0x0400003C>;

	using background2_matrix = omemmap<gba::mat2<gba::make_fixed<8, 8>>, 0x04000020>;
	using background2_origin = omemmap<gba::vec2<gba::make_fixed<20, 8>>, 0x04000028>;

	using background3_matrix = omemmap<gba::mat2<gba::make_fixed<8, 8>>, 0x04000030>;
	using background3_origin = omemmap<gba::vec2<gba::make_fixed<20, 8>>, 0x04000038>;

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
