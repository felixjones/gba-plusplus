#ifndef GBAXX_IRQ_FLAGS_HPP
#define GBAXX_IRQ_FLAGS_HPP

#include <gba/int.hpp>

namespace gba {
namespace irq {

using master_enable = uint32;

struct flags {

	bool	vblank : 1,
			hblank : 1,
			vcounter : 1,
			timer0 : 1,
			timer1 : 1,
			timer2 : 1,
			timer3 : 1,
			serial_comm : 1;

	bool	dma0 : 1,
			dma1 : 1,
			dma2 : 1,
			dma3 : 1,
			keypad : 1,
			game_pak : 1,
			: 2;

} __attribute__((packed));

} // irq
} // gba

#endif // define GBAXX_IRQ_FLAGS_HPP