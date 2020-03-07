#ifndef GBAXX_BIOS_HPP
#define GBAXX_BIOS_HPP

namespace gba {
namespace bios {

inline void vblank_intr_wait() {
#if defined( __thumb__ )
	__asm__ volatile (
		"swi %0\t\n" : : "g"( 0x5 ) : "r0", "r1"
	);
#else
	__asm__ volatile (
		"swi %0 << 16\t\n" : : "g"( 0x5 ) : "r0", "r1"
	);
#endif
}

} // bios
} // gba

#endif // define GBAXX_BIOS_HPP
