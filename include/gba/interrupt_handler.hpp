#ifndef GBAXX_INTERRUPT_HANDLER_HPP
#define GBAXX_INTERRUPT_HANDLER_HPP

#include <gba/interrupt.hpp>

namespace gba {

struct interrupt_condition {
	unsigned mask;
	void ( * function )( void );
};

template <class... Entries>
struct jump_table {
	const interrupt_condition table[sizeof...( Entries )];
	const int zero;

	constexpr jump_table( Entries&&... entries ) : table { std::forward<Entries>( entries )... }, zero( 0 ) {}
};

namespace interrupt_handler {

namespace detail {

	[[gnu::naked, gnu::target( "arm" ), gnu::section( ".iwram" )]]
	static void jump_table_handler() {
		__asm__ volatile (
			"mov r3, #0x4000000\n\t" // REG_BASE
			"ldr r2, [r3, #0x200]\n\t" // Read REG_IE
		);

		__asm__ volatile ( // Get raised flags
			"and r0, r2, r2, lsr #16\n\t" // r0 = IE & IF
		);

		__asm__ volatile ( // combine with BIOS IRQ flags (0x3FFFFF8 mirror)
			"ldrh r2, [r3, #-8]\n\t"
			"orr r2, r2, r0\n\t"
			"strh r2, [r3, #-8]\n\t"
		);

		__asm__ volatile (
			"add r3, r3, #0x200\n\t"
			"strh r0, [r3, #2]\n\t" // IF Clear
		);

		__asm__ volatile ( // Switch to system mode (IRQ stays disabled)
			"msr cpsr_c, #0x9F\n\t"
		);

		// r1 = 0x3000000
		__asm__ volatile (
			"mov r1, #0x3000000\n\t"
		);

		// r2 = *r1
		__asm__ volatile (
			"ldr r2, [r1]\n\t"
		);

		__asm__ volatile (
			".start:\n\t"
		);

		// r1 = r2->mask
		__asm__ volatile (
			"ldr r1, [r2]\n\t"
		);

		// if ( mask == 0 )
		__asm__ volatile (
			"cmp r1, #0\n\t"
			"beq .end\n\t"
		);

		__asm__ volatile (
			"tst r1, r0\n\t"
			"beq .continue\n\t"
		);

		// r3 = r2->function
		__asm__ volatile (
			"ldr r1, [r2, #4]\n\t"
		);

		// function();
		__asm__ volatile (
			"push {r0-r3, lr}\n\t"
			"mov lr, pc\n\t"
			"bx r1\n\t"
			"pop {r0-r3, lr}\n\t"
		);

		// r2++
		__asm__ volatile (
			".continue:\n\t"
			"add r2, r2, #8\n\t"
			"b .start\n\t"
		);

		__asm__ volatile (
			".end:\n\t"
		);

		__asm__ volatile ( // Switch to IRQ mode (IRQ stays disabled)
			"msr cpsr_c, #0x92\n\t"
			"mov pc, lr\n\t"
		);
	}

	[[gnu::naked, gnu::target( "arm" ), gnu::section( ".iwram" )]]
	static void empty_interrupt_handler() {
		__asm__ volatile (
			"mov r3, #0x4000000\n\t"
			"mov r2, #0xFF\n\t"
			"strh r2, [r3, #-8]\n\t"
			"add r3, r3, #0x200\n\t"
			"strh r2, [r3, #2]\n\t"
			"mov pc, lr\n\t"
		);
	}

	[[gnu::naked, gnu::target( "arm" ), gnu::section( ".iwram" )]]
	static void wrapped_handler() {
		__asm__ volatile (
			"mov r3, #0x4000000\n\t" // REG_BASE
			"ldr r2, [r3, #0x200]\n\t" // Read REG_IE
		);

		__asm__ volatile ( // Get raised flags
			"and r0, r2, r2, lsr #16\n\t" // r0 = IE & IF
		);

		__asm__ volatile ( // combine with BIOS IRQ flags (0x3FFFFF8 mirror)
			"ldrh r2, [r3, #-8]\n\t"
			"orr r2, r2, r0\n\t"
			"strh r2, [r3, #-8]\n\t"
		);

		__asm__ volatile (
			"add r3, r3, #0x200\n\t"
			"strh r0, [r3, #2]\n\t" // IF Clear
		);

		__asm__ volatile ( // Switch to system mode (IRQ stays disabled)
			"msr cpsr_c, #0x9F\n\t"
		);
		
		__asm__ volatile (
			"mov r1, #0x3000000\n\t"
			"ldr r1, [r1]\n\t"
			"stmfd sp!, {lr}\n\t"
			"mov lr, pc\n\t"
			"bx r1\n\t"
			"ldmfd sp!, {lr}\n\t"
		);

		__asm__ volatile ( // Switch to IRQ mode (IRQ stays disabled)
			"msr cpsr_c, #0x92\n\t"
			"mov pc, lr\n\t"
		);
	}

} // detail

template <class JumpTable>
[[maybe_unused]]
inline void set( const JumpTable& table ) noexcept {
	using vector_type = void( * )( void );

	*( volatile const JumpTable ** )0x3000000 = &table;
	*( volatile vector_type * )0x3007FFC = detail::jump_table_handler;
}

[[maybe_unused]]
inline void set( [[maybe_unused]] std::nullopt_t ) noexcept {
	using vector_type = void( * )( void );

	*( volatile vector_type * )0x3007FFC = detail::empty_interrupt_handler;
}

[[maybe_unused]]
inline void set( void ( * handler )( interrupt ) ) noexcept {
	using handler_type = decltype( handler );
	using vector_type = void( * )( void );

	*( volatile handler_type * )0x3000000 = handler;
	*( volatile vector_type * )0x3007FFC = detail::wrapped_handler;
}

[[maybe_unused]]
inline void set_raw( void ( * armHandler )( void ) ) noexcept {
	using vector_type = decltype( armHandler );

	*( volatile vector_type * )0x3007FFC = armHandler;
}

} // interrupt_handler
} // gba

#endif // define GBAXX_INTERRUPT_HANDLER_HPP
