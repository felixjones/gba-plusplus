#ifndef GBAXX_BIOS_ASM_HPP
#define GBAXX_BIOS_ASM_HPP

#include <gba/cpu.hpp>
#include <gba/int.hpp>

namespace gba {
namespace bios {
namespace swi {

[[noreturn]]
inline void soft_reset() noexcept {
#if defined( __thumb__ )
	__asm__( "swi\t#0" );
#else
	__asm__( "swi\t#0 << 16" );
#endif
	__builtin_unreachable();
}

inline void register_ram_reset( uint32 flags ) noexcept {
#if defined( __thumb__ )
	__asm__(
		"movs\tr0, %0\n\t"
		"swi\t#1"
		: : "rMI"( flags ) : "r0"
	);
#else
	__asm__(
		"mov\tr0, %0\n\t"
		"swi\t#1 << 16"
		: : "rM"( flags ) : "r0"
	);
#endif
}

inline void halt() noexcept {
#if defined( __thumb__ )
	__asm__( "swi\t#2" );
#else
	__asm__( "swi\t#2 << 16" );
#endif
}

inline void stop() noexcept {
#if defined( __thumb__ )
	__asm__( "swi\t#3" );
#else
	__asm__( "swi\t#3 << 16" );
#endif
}

inline void intr_wait( uint32 clearFlags, uint32 flags ) noexcept {
#if defined( __thumb__ )
	__asm__(
		"movs\tr0, %0\n\t"
		"movs\tr1, %1\n\t"
		"swi\t#4"
		: : "rMI"( clearFlags ), "rMI"( flags ) : "r0", "r1"
	);
#else
	__asm__(
		"mov\tr0, %0\n\t"
		"mov\tr1, %1\n\t"
		"swi\t#4 << 16"
		: : "rM"( clearFlags ), "rM"( flags ) : "r0", "r1"
	);
#endif
}

inline void vblank_intr_wait() noexcept {
#if defined( __thumb__ )
	__asm__( "swi\t#5" );
#else
	__asm__( "swi\t#5 << 16" );
#endif
}

struct [[nodiscard]] div_result {
	int32 r0;
	int32 r1;
	uint32 r2;
};

[[gnu::const]]
inline auto div( const int32 a, const int32 b ) noexcept {
	div_result out;

#if defined( __thumb__ )
	__asm__(
		"movs\tr0, %3\n\t"
		"movs\tr1, %4\n\t"
		"swi\t#6\n\t"
		"str\tr0, %0\n\t"
		"str\tr1, %1\n\t"
		"str\tr3, %2"
		: "=m"( out.r0 ), "=m"( out.r1 ), "=m"( out.r2 ) : "rMI"( a ), "rMI"( b ) : "r0", "r1", "r3"
	);
#else
	__asm__(
		"mov\tr0, %3\n\t"
		"mov\tr1, %4\n\t"
		"swi\t#6 << 16\n\t"
		"str\tr0, %0\n\t"
		"str\tr1, %1\n\t"
		"str\tr3, %2"
		: "=m"( out.r0 ), "=m"( out.r1 ), "=m"( out.r2 ) : "rM"( a ), "rM"( b ) : "r0", "r1", "r3"
	);
#endif

	return out;
}

[[gnu::const]]
inline auto div_arm( const int32 a, const int32 b ) noexcept {
	div_result out;

#if defined( __thumb__ )
	__asm__(
		"movs\tr0, %3\n\t"
		"movs\tr1, %4\n\t"
		"swi\t#7\n\t"
		"str\tr0, %0\n\t"
		"str\tr1, %1\n\t"
		"str\tr3, %2"
		: "=m"( out.r0 ), "=m"( out.r1 ), "=m"( out.r2 ) : "rMI"( a ), "rMI"( b ) : "r0", "r1", "r3"
	);
#else
	__asm__(
		"mov\tr0, %3\n\t"
		"mov\tr1, %4\n\t"
		"swi\t#7 << 16\n\t"
		"str\tr0, %0\n\t"
		"str\tr1, %1\n\t"
		"str\tr3, %2"
		: "=m"( out.r0 ), "=m"( out.r1 ), "=m"( out.r2 ) : "rM"( a ), "rM"( b ) : "r0", "r1", "r3"
	);
#endif

	return out;
}

[[gnu::const, nodiscard]]
inline uint32 sqrt( const uint32 x ) noexcept {
#if defined( __thumb__ )
	__asm__(
		"movs\tr0, %0\n\t"
		"swi\t#8"
		: : "ri"( x ) : "r0"
	);
#else
	__asm__(
		"mov\tr0, %0\n\t"
		"swi\t#8 << 16"
		: : "ri"( x ) : "r0"
	);
#endif
	return cpu::iregister<uint32, 0>::read();
}

[[gnu::const, nodiscard]]
inline int32 arc_tan( const int32 x ) noexcept {
#if defined( __thumb__ )
	__asm__(
		"movs\tr0, %0\n\t"
		"swi\t#9" 
		: : "r"( x ) : "r0"
	);
#else
	__asm__(
		"mov\tr0, %0\n\t"
		"swi\t#9 << 16" 
		: : "ri"( x ) : "r0"
	);
#endif
	return cpu::iregister<int32, 0>::read();
}

[[gnu::const, nodiscard]]
inline uint32 arc_tan2( const int32 x, const int32 y ) noexcept {
#if defined( __thumb__ )
	__asm__(
		"movs\tr0, %0\n\t"
		"movs\tr1, %1\n\t"
		"swi\t#10" 
		: : "r"( x ), "r"( y ) : "r0", "r1"
	);
#else
	__asm__(
		"mov\tr0, %0\n\t"
		"mov\tr1, %1\n\t"
		"swi\t#10 << 16" 
		: : "ri"( x ), "ri"( y ) : "r0", "r1"
	);
#endif
	return cpu::iregister<uint32, 0>::read();
}

inline void cpu_set( const uint32 src, const uint32 dst, const uint32 lengthMode ) {
#if defined( __thumb__ )
	__asm__(
		"movs\tr0, %0\n\t"
		"movs\tr1, %1\n\t"
		"movs\tr2, %2\n\t"
		"swi\t#11" 
		: : "r"( src ), "r"( dst ), "r"( lengthMode ) : "r0", "r1", "r2"
	);
#else
	__asm__(
		"mov\tr0, %0\n\t"
		"mov\tr1, %1\n\t"
		"mov\tr2, %2\n\t"
		"swi\t#11 << 16" 
		: : "ri"( src ), "ri"( dst ), "ri"( lengthMode ) : "r0", "r1", "r2"
	);
#endif
}

inline void cpu_fast_set( const uint32 src, const uint32 dst, const uint32 lengthMode ) {
#if defined( __thumb__ )
	__asm__(
		"movs\tr0, %0\n\t"
		"movs\tr1, %1\n\t"
		"movs\tr2, %2\n\t"
		"swi\t#12" 
		: : "ri"( src ), "ri"( dst ), "ri"( lengthMode ) : "r0", "r1", "r2"
	);
#else
	__asm__(
		"mov\tr0, %0\n\t"
		"mov\tr1, %1\n\t"
		"mov\tr2, %2\n\t"
		"swi\t#12 << 16" 
		: : "ri"( src ), "ri"( dst ), "ri"( lengthMode ) : "r0", "r1", "r2"
	);
#endif
}

namespace undocumented {

	[[noreturn]]
	inline void hard_reset() noexcept {
#if defined( __thumb__ )
		__asm__( "swi\t#38" );
#else
		__asm__( "swi\t#38 << 16" );
#endif
		__builtin_unreachable();
	}

	[[gnu::const, nodiscard]]
	inline uint32 get_bios_checksum() noexcept {
#if defined( __thumb__ )
		__asm__(
			"swi\t#13"
			: : : "r0"
		);
#else
		__asm__(
			"swi\t#13 << 16"
			: : : "r0"
		);
#endif
		return cpu::iregister<uint32, 0>::read();
	}

} // undocumented

} // swi
} // bios
} // gba

#endif // define GBAXX_BIOS_ASM_HPP
