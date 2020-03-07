#ifndef GBAXX_INTERRUPT_HANDLER_HPP
#define GBAXX_INTERRUPT_HANDLER_HPP

namespace gba {
namespace interrupt_handler {

using vector_type = void( * )( void );

[[gnu::naked, gnu::target( "arm" ), gnu::section( ".iwram" )]]
static void empty_handler() {
	__asm__ volatile (
		"mov r3, #0x4000000\n\t"
		"mov r2, #0xFF\n\t"
		"strh r2, [r3, #-8]\n\t"
		"add r3, r3, #0x200\n\t"
		"strh r2, [r3, #2]\n\t"
		"mov pc, lr\n\t"
	);
}

} // interrupt_handler
} // gba

#endif // define GBAXX_INTERRUPT_HANDLER_HPP
