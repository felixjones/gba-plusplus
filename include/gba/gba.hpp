#ifndef GBAXX_GBA_HPP
#define GBAXX_GBA_HPP

#include <gba/background_control.hpp>
#include <gba/bios.hpp>
#include <gba/bit.hpp>
#include <gba/blending.hpp>
#include <gba/bool.hpp>
#include <gba/bool_type.hpp>
#include <gba/const.hpp>
#include <gba/display_control.hpp>
#include <gba/display_status.hpp>
#include <gba/dma_control.hpp>
#include <gba/fixed_point.hpp>
#include <gba/int.hpp>
#include <gba/int_type.hpp>
#include <gba/interrupt.hpp>
#include <gba/interrupt_handler.hpp>
#include <gba/keypad.hpp>
#include <gba/mat2.hpp>
#include <gba/mat3.hpp>
#include <gba/mat4.hpp>
#include <gba/math.hpp>
#include <gba/memmap.hpp>
#include <gba/mosaic.hpp>
#include <gba/oam.hpp>
#include <gba/printstream.hpp>
#include <gba/tile.hpp>
#include <gba/timer_control.hpp>
#include <gba/type_promotion.hpp>
#include <gba/vec2.hpp>
#include <gba/vec3.hpp>
#include <gba/vec4.hpp>
#include <gba/window.hpp>

namespace gba {
namespace io {
	using display_control = iomemmap<gba::display_control, 0x04000000>;

	using display_status = iomemmap<gba::display_status, 0x04000004>;
	using vertical_counter = imemmap<gba::uint16, 0x04000006>;

	using background0_control = iomemmap<gba::background_control, 0x04000008>;
	using background1_control = iomemmap<gba::background_control, 0x0400000A>;
	using background2_control = iomemmap<gba::background_control, 0x0400000C>;
	using background3_control = iomemmap<gba::background_control, 0x0400000E>;

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
	using background2_offset = omemmap<gba::vec2<gba::make_fixed<20, 8>>, 0x04000028>;

	using background3_matrix = omemmap<gba::mat2<gba::make_fixed<8, 8>>, 0x04000030>;
	using background3_offset = omemmap<gba::vec2<gba::make_fixed<20, 8>>, 0x04000038>;

	using window0_hdim = omemmap<gba::dim<gba::uint8>, 0x04000040>;
	using window1_hdim = omemmap<gba::dim<gba::uint8>, 0x04000042>;

	using window0_vdim = omemmap<gba::dim<gba::uint8>, 0x04000044>;
	using window1_vdim = omemmap<gba::dim<gba::uint8>, 0x04000046>;

	using window0_inside_control = iomemmap<gba::window_control, 0x04000048>;
	using window1_inside_control = iomemmap<gba::window_control, 0x04000049>;

	using window0_outside_control = iomemmap<gba::window_control, 0x0400004A>;
	using window1_outside_control = iomemmap<gba::window_control, 0x0400004B>;

	using mosaic_control = omemmap<gba::mosaic_control, 0x0400004C>;

	using blend_control = iomemmap<gba::blend_control, 0x04000050>;
	using blend_alpha = iomemmap<gba::blend_alpha, 0x04000052>;
	using blend_gamma = omemmap<gba::fixed_point<uint16, 4>, 0x04000054>;

	using key_status = imemmap<gba::keys, 0x04000130>;

	using interrupt_master_enable = iomemmap<gba::bool32, 0x04000208>;
	using interrupt_mask_enable = iomemmap<gba::interrupt, 0x04000200>;
	using interrupt_flags = iomemmap<gba::interrupt, 0x04000202>;

	using timer0_start = omemmap<uint16, 0x04000100>;
	using timer0_counter = imemmap<uint16, 0x04000100>;
	using timer0_control = iomemmap<timer_control, 0x04000102>;

	using timer1_start = omemmap<uint16, 0x04000104>;
	using timer1_counter = imemmap<uint16, 0x04000104>;
	using timer1_control = iomemmap<timer_control, 0x04000106>;

	using timer2_start = omemmap<uint16, 0x04000108>;
	using timer2_counter = imemmap<uint16, 0x04000108>;
	using timer2_control = iomemmap<timer_control, 0x0400010A>;

	using timer3_start = omemmap<uint16, 0x0400010C>;
	using timer3_counter = imemmap<uint16, 0x0400010C>;
	using timer3_control = iomemmap<timer_control, 0x0400010E>;

	using dma0_address_source = omemmap<uintptr, 0x040000B0>;
	using dma0_address_destination = omemmap<uintptr, 0x040000B4>;
	using dma0_count = omemmap<uint16, 0x040000B8>;
	using dma0_control = iomemmap<dma_control, 0x040000BA>;

	using dma1_address_source = omemmap<uintptr, 0x040000BC>;
	using dma1_address_destination = omemmap<uintptr, 0x040000C0>;
	using dma1_count = omemmap<uint16, 0x040000C4>;
	using dma1_control = iomemmap<dma_control, 0x040000C6>;

	using dma2_address_source = omemmap<uintptr, 0x040000C8>;
	using dma2_address_destination = omemmap<uintptr, 0x040000CC>;
	using dma2_count = omemmap<uint16, 0x040000D0>;
	using dma2_control = iomemmap<dma_control, 0x040000D2>;

	using dma3_address_source = omemmap<uintptr, 0x040000D4>;
	using dma3_address_destination = omemmap<uintptr, 0x040000D8>;
	using dma3_count = omemmap<uint16, 0x040000DC>;
	using dma3_control = iomemmap<dma_control, 0x040000DE>;

} // io

namespace undocumented {
namespace io {
	using display_control_green_swap = iomemmap<gba::bool16, 0x04000002>;

	using post_flag = iomemmap<gba::bool8, 0x04000300>;
	using halt_control = omemmap<gba::bool_type<8, 7>, 0x04000301>;
} // io
} // undocumented
} // gba

#endif // define GBAXX_GBA_HPP
