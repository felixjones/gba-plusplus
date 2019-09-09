#ifndef GBAXX_IRQ_HANDLER_HPP
#define GBAXX_IRQ_HANDLER_HPP

namespace gba {
namespace irq {

typedef void ( * vector_type )( void );

template <void( * Runnable )( void )>
constexpr vector_type handler() {
	class handler_impl {
	private:
		static void end() __attribute__( ( naked, target( "arm" ) ) ) {
			asm( "ldmia sp!, {lr}\n\t" );

			// Switch to IRQ mode
			asm( "mrs r2, cpsr\n\t"
				 "bic r2, r2, #0x1F\n\t"
				 "orr r2, r2, #0x92\n\t"
				 "msr cpsr_cf, r2\n\t" );

			// Restore IRQ stack pointer and IME
			asm( "ldmia sp!, {r0-r2,lr}\n\t"
				 "strh r1, [r2, #8]\n\t"
				 "msr spsr_cf, r0\n\t" );

			// Return to BIOS IRQ handler
			asm( "bx lr\n\t" );
		}

	public:
		static void start() __attribute__( ( naked, target( "arm" ) ) ) {
			// Load base I/O register address
			asm( "mov r2, #0x04000000\n\t"
				 "add r2, r2, #0x200\n\t" );

			// Save IRQ stack pointer and IME
			asm( "mrs r0, spsr\n\t"
				 "ldrh r1, [r2, #8]\n\t"
				 "stmdb sp!, {r0-r2,lr}\n\t" );

			// Disable all interrupts by writing to IME
			asm( "mov r0, #0\n\t"
				 "strh r0, [r2, #8]\n\t" );

			// Acknowledge all received interrupts that were enabled in IE
			asm( "ldr r3, [r2, #0]\n\t"
				 "and r0, r3, r3, lsr #16\n\t"
				 "strh r0, [r2, #2]\n\t" );

			// Switch to system mode
			asm( "mrs r2, cpsr\n\t"
				 "bic r2, r2, #0x1F\n\t"
				 "orr r2, r2, #0x1F\n\t"
				 "msr cpsr_cf, r2\n\t" );

			// Jump to user specified IRQ handler
			asm( "stmdb sp!, {lr}\n\t"
				 "mov lr, %[handlerEnd]\n\t"
				 "bx %[handlerRunnable]\n\t" : : [handlerEnd] "r"( handler_impl::end ), [handlerRunnable]"r"( Runnable ) );
		}
	};

	return handler_impl::start;
}

template <void( * Runnable )( int )>
constexpr vector_type handler() {
	class handler_impl {
	private:
		static void end() __attribute__( ( naked, target( "arm" ) ) ) {
			asm( "ldmia sp!, {lr}\n\t" );

			// Switch to IRQ mode
			asm( "mrs r2, cpsr\n\t"
				 "bic r2, r2, #0x1F\n\t"
				 "orr r2, r2, #0x92\n\t"
				 "msr cpsr_cf, r2\n\t" );

			// Restore IRQ stack pointer and IME
			asm( "ldmia sp!, {r0-r2,lr}\n\t"
				 "strh r1, [r2, #8]\n\t"
				 "msr spsr_cf, r0\n\t" );

			// Return to BIOS IRQ handler
			asm( "bx lr\n\t" );
		}

	public:
		static void start() __attribute__( ( naked, target( "arm" ) ) ) {
			// Load base I/O register address
			asm( "mov r2, #0x04000000\n\t"
				 "add r2, r2, #0x200\n\t" );

			// Save IRQ stack pointer and IME
			asm( "mrs r0, spsr\n\t"
				 "ldrh r1, [r2, #8]\n\t"
				 "stmdb sp!, {r0-r2,lr}\n\t" );

			// Disable all interrupts by writing to IME
			asm( "mov r0, #0\n\t"
				 "strh r0, [r2, #8]\n\t" );

			// Acknowledge all received interrupts that were enabled in IE
			asm( "ldr r3, [r2, #0]\n\t"
				 "and r0, r3, r3, lsr #16\n\t"
				 "strh r0, [r2, #2]\n\t" );

			// Switch to system mode
			asm( "mrs r2, cpsr\n\t"
				 "bic r2, r2, #0x1F\n\t"
				 "orr r2, r2, #0x1F\n\t"
				 "msr cpsr_cf, r2\n\t" );

			// Jump to user specified IRQ handler
			asm( "stmdb sp!, {lr}\n\t"
				 "mov lr, %[handlerEnd]\n\t"
				 "bx %[handlerRunnable]\n\t" : : [handlerEnd] "r"( handler_impl::end ), [handlerRunnable]"r"( Runnable ) );
		}
	};

	return handler_impl::start;
}

} // irq
} // gba

#endif // define GBAXX_IRQ_HANDLER_HPP
