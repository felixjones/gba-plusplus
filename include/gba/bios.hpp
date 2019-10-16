#ifndef GBAXX_BIOS_HPP
#define GBAXX_BIOS_HPP

#include <gba/bit_bool.hpp>
#include <gba/bool.hpp>
#include <gba/irq.hpp>

namespace gba {
namespace bios {

[[gnu::unused]]
static void intr_wait( [[gnu::unused]] bool32 clearFlags, [[gnu::unused]] irq::bits waitFlags ) {
#if defined( __thumb__ )
	asm(
		"swi %0\t\n" : : "g"( 0x4 ) : "r0", "r1"
	);
#else
	asm(
		"swi %0 << 16\t\n" : : "g"( 0x4 ) : "r0", "r1"
	);
#endif
}

[[gnu::unused]]
static void vblank_intr_wait() {
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

[[gnu::unused]]
static void custom_halt( [[gnu::unused]] bit_bool<uint32, 7> stop ) {
#if defined( __thumb__ )
	asm(
		"swi %0\t\n" : : "g"( 0x27 ) : "r0"
	);
#else
	asm(
		"swi %0 << 16\t\n" : : "g"( 0x27 ) : "r0"
	);
#endif
}

} // undocumented

} // bios
} // gba

#endif // define GBAXX_BIOS_HPP

/*
#include <tuple>
#include <gba/int.hpp>

template <unsigned Number>
void swi() {
#if defined( __thumb__ )
	asm(
		"swi %0\t\n" : : "g"( Number )
	);
#else
	asm(
		"swi %0 << 16\t\n" : : "g"( Number )
	);
#endif
}

inline std::tuple<int32, int32, uint32> div( int32 numerator, int32 denominator ) {
	auto r0 asm( "r0" ) = numerator;
	auto r1 asm( "r1" ) = denominator;
	uint32 r3 asm( "r3" );

#if defined( __thumb__ )
	asm(
		"swi %0\t\n" : "=r"( r0 ), "=r"( r1 ), "=r"( r3 ) : "g"( 0x6 ) : "r0", "r1", "r3"
	);
#else
	asm(
		"swi %0 << 16\t\n" : "=r"( r0 ), "=r"( r1 ), "=r"( r3 ) : "g"( 0x6 ) : "r0", "r1", "r3"
	);
#endif

	return { r0, r1, r3 };
}

inline std::tuple<int32, int32, uint32> div_arm( int32 denominator, int32 numerator ) {
	auto r0 asm( "r0" ) = denominator;
	auto r1 asm( "r1" ) = numerator;
	uint32 r3 asm( "r3" );

#if defined( __thumb__ )
	asm(
		"swi %0\t\n" : "=r"( r0 ), "=r"( r1 ), "=r"( r3 ) : "g"( 0x7 ) : "r0", "r1", "r3"
	);
#else
	asm(
		"swi %0 << 16\t\n" : "=r"( r0 ), "=r"( r1 ), "=r"( r3 ) : "g"( 0x7 ) : "r0", "r1", "r3"
	);
#endif

	return { r0, r1, r3 };
}

static uint32 sqrt( uint32 value ) {
	auto r0 asm( "r0" ) = value;

#if defined( __thumb__ )
	asm(
		"swi %0\t\n" : "=r"( r0 ) : "g"( 0x8 ) : "r0"
	);
#else
	asm(
		"swi %0 << 16\t\n" : "=r"( r0 ) : "g"( 0x8 ) : "r0"
	);
#endif

	return r0;
}

constexpr auto halt = swi<0x02>;
constexpr auto stop = swi<0x03>;

*/
