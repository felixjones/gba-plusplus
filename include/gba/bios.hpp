#ifndef GBAXX_BIOS_HPP
#define GBAXX_BIOS_HPP

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

template <class ReprType, int Exponent>
auto sqrt( const fixed_point<ReprType, Exponent>& x ) noexcept {
	using exp_even_type = fixed_point<uint32, Exponent - ( Exponent % 2 )>;
	using exp_half_type = fixed_point<uint32, exp_even_type::exponent / 2>;

	const auto resultData = sqrt( exp_even_type( x ).data() );
	const auto resultFixed = exp_half_type::from_data( resultData );
	return fixed_point<ReprType, Exponent>( resultFixed );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_HPP
