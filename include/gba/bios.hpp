#ifndef GBAXX_BIOS_HPP
#define GBAXX_BIOS_HPP

#include <tuple>
#include <type_traits>

#include <gba/fixed_point.hpp>
#include <gba/int.hpp>

namespace gba {
namespace bios {

inline void vblank_intr_wait() {
#if defined( __thumb__ )
	__asm__ volatile (
		"swi %0\n\t"
			: : "g"( 0x5 ) : "r0", "r1"
	);
#else
	__asm__ volatile (
		"swi %0 << 16\n\t"
			: : "g"( 0x5 ) : "r0", "r1"
	);
#endif
}

inline std::tuple<int32, int32, uint32> div( volatile int32 a, volatile int32 b ) noexcept {
	volatile uint32 c;

#if defined( __thumb__ )
	__asm__ volatile (
		"mov r0, %4\n\t"
		"mov r1, %5\n\t"
		"swi %3\n\t"
		"mov %0, r0\n\t"
		"mov %1, r1\n\t"
		"mov %2, r3\n\t"
			: "=r"( a ), "=r"( b ), "=r"( c ) : "g"( 0x6 ), "r"( a ), "r"( b ) : "r0", "r1", "r3"
	);
#else
	__asm__ volatile (
		"mov r0, %4\n\t"
		"mov r1, %5\n\t"
		"swi %3 << 16\n\t"
		"mov %0, r0\n\t"
		"mov %1, r1\n\t"
		"mov %2, r3\n\t"
			: "=r"( a ), "=r"( b ), "=r"( c ) : "g"( 0x6 ), "r"( a ), "r"( b ) : "r0", "r1", "r3"
	);
#endif

	return std::make_tuple( a, b, c );
}

inline std::tuple<int32, int32, uint32> div_arm( volatile int32 a, volatile int32 b ) noexcept {
	volatile uint32 c;

#if defined( __thumb__ )
	__asm__ volatile (
		"mov r0, %5\n\t"
		"mov r1, %4\n\t"
		"swi %3\n\t"
		"mov %0, r0\n\t"
		"mov %1, r1\n\t"
		"mov %2, r3\n\t"
			: "=r"( a ), "=r"( b ), "=r"( c ) : "g"( 0x7 ), "r"( a ), "r"( b ) : "r0", "r1", "r3"
	);
#else
	__asm__ volatile (
		"mov r0, %5\n\t"
		"mov r1, %4\n\t"
		"swi %3 << 16\n\t"
		"mov %0, r0\n\t"
		"mov %1, r1\n\t"
		"mov %2, r3\n\t"
			: "=r"( a ), "=r"( b ), "=r"( c ) : "g"( 0x7 ), "r"( a ), "r"( b ) : "r0", "r1", "r3"
	);
#endif

	return std::make_tuple( a, b, c );
}

template <class T>
[[gnu::naked]]
inline auto sqrt( T x ) noexcept -> typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value, T>::type {
#if defined( __thumb__ )
	__asm__ volatile (
		"swi %0\n\t" 
		"bx lr\n\t"
			: : "g"( 0x8 ) : "r0"
	);
#else
	__asm__ volatile (
		"swi %0 << 16\n\t" 
		"bx lr\n\t"
			: : "g"( 0x8 ) : "r0"
	);
#endif
}

template <typename ReprType, unsigned ExpBits>
auto sqrt( const fixed_point<ReprType, ExpBits>& x ) noexcept {
	using exp_even_type = fixed_point<uint32, ExpBits - ( ExpBits % 2 )>;
	using exp_half_type = fixed_point<uint32, exp_even_type::exponent / 2>;

	const auto resultData = sqrt( exp_even_type( x ).data() );
	const auto resultFixed = exp_half_type::from_data( resultData );
	return fixed_point<ReprType, ExpBits>( resultFixed );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_HPP
