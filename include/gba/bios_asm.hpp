#ifndef GBAXX_BIOS_ASM_HPP
#define GBAXX_BIOS_ASM_HPP

#include <gba/cpu.hpp>
#include <gba/int.hpp>

namespace gba {
namespace bios {
namespace swi {

#if defined( __thumb__ )
#define GBAXX_SWI_CALL( NUM )	__asm__( "swi\t#"#NUM )
#else
#define GBAXX_SWI_CALL( NUM )	__asm__( "swi\t#"#NUM" << 16" )
#endif

[[noreturn]]
inline void soft_reset() noexcept {
	GBAXX_SWI_CALL( 0 );
	__builtin_unreachable();
}

inline void register_ram_reset( uint32 flags ) noexcept {
	cpu::oregister<uint32, 0>::write( flags );
	GBAXX_SWI_CALL( 1 );
}

inline void halt() noexcept {
	GBAXX_SWI_CALL( 2 );
}

inline void stop() noexcept {
	GBAXX_SWI_CALL( 3 );
}

inline void intr_wait( uint32 clearFlags, uint32 flags ) noexcept {
	cpu::oregister<uint32, 0>::write( clearFlags );
	cpu::oregister<uint32, 1>::write( flags );
	GBAXX_SWI_CALL( 4 );
}

inline void vblank_intr_wait() noexcept {
#if defined( __thumb__ )
	__asm__( "swi\t#5" ::: "r0", "r1" );
#else
	__asm__( "swi\t#5 << 16" ::: "r0", "r1" );
#endif
}

struct [[nodiscard]] div_result {
	int32 r0;
	int32 r1;
	uint32 r2;
};

[[gnu::const]]
inline auto div( const int32 a, const int32 b ) noexcept {
	cpu::oregister<int32, 0>::write( a );
	cpu::oregister<int32, 1>::write( b );

	div_result out;
#if defined( __thumb__ )
	__asm__(
		"swi\t#6\n\t"
		"str\tr0, %0\n\t"
		"str\tr1, %1\n\t"
		"str\tr3, %2"
		: "=m"( out.r0 ), "=m"( out.r1 ), "=m"( out.r2 ) :: "r0", "r1", "r3", "cc"
	);
#else
	__asm__(
		"swi\t#6 << 16\n\t"
		"str\tr0, %0\n\t"
		"str\tr1, %1\n\t"
		"str\tr3, %2"
		: "=m"( out.r0 ), "=m"( out.r1 ), "=m"( out.r2 ) :: "r0", "r1", "r3"
	);
#endif
	return out;
}

[[gnu::const]]
inline auto div_arm( const int32 a, const int32 b ) noexcept {
	cpu::oregister<int32, 0>::write( a );
	cpu::oregister<int32, 1>::write( b );

	div_result out;
#if defined( __thumb__ )
	__asm__(
		"swi\t#7\n\t"
		"str\tr0, %0\n\t"
		"str\tr1, %1\n\t"
		"str\tr3, %2"
		: "=m"( out.r0 ), "=m"( out.r1 ), "=m"( out.r2 ) :: "r0", "r1", "r3"
	);
#else
	__asm__(
		"swi\t#7 << 16\n\t"
		"str\tr0, %0\n\t"
		"str\tr1, %1\n\t"
		"str\tr3, %2"
		: "=m"( out.r0 ), "=m"( out.r1 ), "=m"( out.r2 ) :: "r0", "r1", "r3"
	);
#endif
	return out;
}

[[gnu::const, nodiscard]]
inline uint32 sqrt( const uint32 x ) noexcept {
	using r0 = cpu::ioregister<uint32, 0>;

	r0::write( x );
	GBAXX_SWI_CALL( 8 );
	return r0::read();
}

[[gnu::const, nodiscard]]
inline int32 arc_tan( const int32 x ) noexcept {
	using r0 = cpu::ioregister<int32, 0>;

	r0::write( x );
	GBAXX_SWI_CALL( 9 );
	return r0::read();
}

[[gnu::const, nodiscard]]
inline uint32 arc_tan2( const int32 x, const int32 y ) noexcept {
	cpu::oregister<int32, 0>::write( x );
	cpu::oregister<int32, 1>::write( y );
	GBAXX_SWI_CALL( 10 );
	return cpu::iregister<uint32, 0>::read();
}

inline void cpu_set( const uint32 src, const uint32 dst, const uint32 lengthMode ) {
	cpu::oregister<uint32, 0>::write( src );
	cpu::oregister<uint32, 1>::write( dst );
	cpu::oregister<uint32, 2>::write( lengthMode );
	GBAXX_SWI_CALL( 11 );
}

inline void cpu_fast_set( const uint32 src, const uint32 dst, const uint32 lengthMode ) {
	cpu::oregister<uint32, 0>::write( src );
	cpu::oregister<uint32, 1>::write( dst );
	cpu::oregister<uint32, 2>::write( lengthMode );
	GBAXX_SWI_CALL( 12 );
}

namespace undocumented {

	[[noreturn]]
	inline void hard_reset() noexcept {
		GBAXX_SWI_CALL( 38 );
		__builtin_unreachable();
	}

	[[gnu::const, nodiscard]]
	inline uint32 get_bios_checksum() noexcept {
		GBAXX_SWI_CALL( 13 );
		return cpu::iregister<uint32, 0>::read();
	}

} // undocumented

#undef GBAXX_SWI_CALL

} // swi
} // bios
} // gba

#endif // define GBAXX_BIOS_ASM_HPP
