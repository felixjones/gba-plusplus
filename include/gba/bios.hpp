#ifndef GBAXX_BIOS_HPP
#define GBAXX_BIOS_HPP

#include <gba/bit_bool.hpp>
#include <gba/bit_cast.hpp>
#include <gba/bool.hpp>
#include <gba/int_type.hpp>
#include <gba/irq.hpp>

namespace gba {
namespace bios {

inline void intr_wait( bool32 clearFlags, irq::bits waitFlags ) {
	const register auto r0 asm( "r0" ) = gba::bit_cast<int>( clearFlags );
	const register auto r1 asm( "r1" ) = gba::bit_cast<short>( waitFlags );
#if defined( __thumb__ )
	asm(
		"swi %0\t\n" : : "g"( 0x4 ), "r"( r0 ), "r"( r1 )
	);
#else
	asm(
		"swi %0 << 16\t\n" : : "g"( 0x4 ), "r"( r0 ), "r"( r1 )
	);
#endif
}

inline void vblank_intr_wait() {
#if defined( __thumb__ )
	asm(
		"swi %0\t\n" : : "g"( 0x5 ) : "r0", "r1"
	);
#else
	asm(
		"swi %0 << 16\t\n" : : "g"( 0x5 ) : "r0", "r1"
	);
#endif
}

namespace undocumented {

inline void custom_halt( bit_bool<uint32, 7> stop ) {
	const register auto r2 asm( "r2" ) = gba::bit_cast<int>( stop );
#if defined( __thumb__ )
	asm(
		"swi %0\t\n" : : "g"( 0x27 ), "r"( r2 ) : "r0", "r1"
	);
#else
	asm(
		"swi %0 << 16\t\n" : : "g"( 0x27 ), "r"( r2 ) : "r0", "r1"
	);
#endif
}

} // undocumented

} // bios
} // gba

#endif // define GBAXX_BIOS_HPP
