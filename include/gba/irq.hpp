#ifndef GBAXX_IRQ_TYPES_HPP
#define GBAXX_IRQ_TYPES_HPP

#include <gba/int.hpp>

namespace gba {
namespace irq {

struct [[gnu::packed]] bits {

	bool	vblank : 1,
			hblank : 1,
			vcounter : 1,
			timer0 : 1,
			timer1 : 1,
			timer2 : 1,
			timer3 : 1,
			serial_communication : 1;

	bool	dma0 : 1,
			dma1 : 1,
			dma2 : 1,
			dma3 : 1,
			keypad : 1,
			game_pak : 1,
			: 2;

};

typedef void ( * handler_type )( void );

// Null handler
constexpr handler_type empty_handler() {
	struct handler_impl0 {
		[[gnu::naked, gnu::target( "arm" ), gnu::section( ".iwram" ), gnu::long_call]]
		static void entry() {
			asm(
				"mov r3, #0x4000000\n\t" // REG_BASE
				"ldr r2, [r3, #0x200]\n\t" // Read REG_IE
			);

			asm( // Get raised flags
				 "and r0, r2, r2, lsr #16\n\t" // r0 = IE & IF
			);

			asm( // combine with BIOS IRQ flags (0x3FFFFF8 mirror)
				 "ldrh r2, [r3, #-8]\n\t"
				 "orr r2, r2, r0\n\t"
				 "strh r2, [r3, #-8]\n\t"
			);

			asm(
				"add r3, r3, #0x200\n\t"
				"strh r0, [r3, #2]\n\t" // IF Clear
			);

			asm(
				 "mov pc, lr\n\t"
			);
		}
	};
	return handler_impl0::entry;
}

// 1 function handler
template <void( * Runnable )( bits )>
constexpr handler_type make_handler() {
	struct handler_impl1 {
		[[gnu::naked, gnu::target( "arm" ), gnu::section( ".iwram" ), gnu::long_call]]
		static void entry() {
			asm(
				"mov r3, #0x4000000\n\t" // REG_BASE
				"ldr r2, [r3, #0x200]\n\t" // Read REG_IE
			);

			asm( // Get raised flags
				"and r0, r2, r2, lsr #16\n\t" // r0 = IE & IF
			);

			asm( // combine with BIOS IRQ flags (0x3FFFFF8 mirror)
				 "ldrh r2, [r3, #-8]\n\t"
				 "orr r2, r2, r0\n\t"
				 "strh r2, [r3, #-8]\n\t"
			);

			asm(
				"add r3, r3, #0x200\n\t"
				"strh r0, [r3, #2]\n\t" // IF Clear
			);

			asm( // Switch to system mode (IRQ stays disabled)
				"msr cpsr_c, #0x9F\n\t"
			);

			asm(
				"stmfd sp!, {lr}\n\t"
				"ldr r1, =%[runnable]\n\t"
				"mov lr, pc\n\t"
				"bx r1\n\t"
				"ldmfd sp!, {lr}\n\t" : : [runnable] "g"( Runnable ) : "r0"
			);

			asm( // Switch to IRQ mode (IRQ stays disabled)
				"msr cpsr_c, #0x92\n\t"
				"mov pc, lr\n\t"
			);
		}
	};
	return handler_impl1::entry;
}

// Multi function handler
template <class... Conditionals>
constexpr handler_type make_handler() {
	struct handler_impl2 {
		[[gnu::naked, gnu::target( "arm" ), gnu::section( ".iwram" ), gnu::long_call]]
		static void entry() {
			asm(
				"mov r3, #0x4000000\n\t" // REG_BASE
				"ldr r2, [r3, #0x200]\n\t" // Read REG_IE
			);

			asm( // Get raised flags
				 "and r0, r2, r2, lsr #16\n\t" // r0 = IE & IF
			);

			asm( // combine with BIOS IRQ flags (0x3FFFFF8 mirror)
				 "ldrh r2, [r3, #-8]\n\t"
				 "orr r2, r2, r0\n\t"
				 "strh r2, [r3, #-8]\n\t"
			);

			asm(
				"add r3, r3, #0x200\n\t"
				"strh r0, [r3, #2]\n\t" // IF Clear
			);

			asm( // Switch to system mode (IRQ stays disabled)
				 "msr cpsr_c, #0x9F\n\t"
			);

			asm(
				"stmfd sp!, {lr}\n\t"
			);

			( []() {
				asm(
					"tst r0, %[Mask]\n\t"
					"ldr r1, =%[runnable]\n\t"
					"mov lr, pc\n\t"
					"bxne r1\n\t" : : [Mask] "g"( Conditionals::mask ), [runnable] "g"( Conditionals::runnable )
				);
			}(), ... );

			asm(
				"ldmfd sp!, {lr}\n\t"
			);

			asm( // Switch to IRQ mode (IRQ stays disabled)
				 "msr cpsr_c, #0x92\n\t"
				 "mov pc, lr\n\t"
			);
		}

	};
	return handler_impl2::entry;
}

// TODO : Nested handler

template <unsigned Mask, void ( * Runnable )( bits )>
struct conditional {
	static constexpr auto mask = Mask;
	static constexpr auto runnable = Runnable;
};

} // irq
} // gba

#endif // define GBAXX_IRQ_TYPES_HPP
