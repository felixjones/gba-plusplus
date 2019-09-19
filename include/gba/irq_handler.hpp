#ifndef GBAXX_IRQ_HANDLER_HPP
#define GBAXX_IRQ_HANDLER_HPP

#include <gba/irq_flags.hpp>

namespace gba {
namespace irq {

// Null handler
constexpr auto make_handler() {
	struct handler_impl0 {
		[[gnu::naked, gnu::target( "arm" ), gnu::section( ".iwram" ), gnu::long_call]]
		static void entry() {
			asm(
				"mov r3, #0x4000000\n\t" // REG_BASE
				"ldr r1, [r3, #0x200]\n\t" // Read REG_IE
				"and r0, r1, r1, lsr #16\n\t" // r0 = IE & IF
			);

			asm( // combine with BIOS IRQ flags (0x3FFFFF8 mirror)
				 "ldrh r1, [r3, #-8]\n\t"
				 "orr r1, r1, r0\n\t"
				 "strh r1, [r3, #-8]\n\t"
			);

			asm(
				"mov pc, lr\n\t"
			);
		}
	};
	return handler_impl0::entry;
}

// 1 function handler
template <void( *Runnable )( flags )>
constexpr auto make_handler() {
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

template <class... Conditionals>
constexpr auto make_handler() {
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

			( []() {
				asm(
					"stmfd sp!, {r0-r1, lr}\n\t"
				);

				asm(
					"ldr r1, =%[run]\n\t"
					"ands r0, r0, %[Mask]\n\t"
					"mov lr, pc\n\t"
					"bxne r1\n\t" : : [Mask] "g"( Conditionals::mask ), [run] "g"( Conditionals::runnable )
				);

				asm(
					"ldmfd sp!, {r0-r1, lr}\n\t"
				);
			}(), ... );

			asm( // Switch to IRQ mode (IRQ stays disabled)
				 "msr cpsr_c, #0x92\n\t"
				 "mov pc, lr\n\t"
			);
		}

	};
	return handler_impl2::entry;
}

typedef void ( *handler_type )( void );

static volatile handler_type& vector = *reinterpret_cast<volatile handler_type *>( 0x3007FFC );

} // irq
} // gba

#endif // define GBAXX_IRQ_HANDLER_HPP
