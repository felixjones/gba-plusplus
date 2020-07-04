#ifndef GBAXX_MATH_CONSTANTS_HPP
#define GBAXX_MATH_CONSTANTS_HPP

#include <gba/int.hpp>
#include <gba/fixed_point.hpp>

namespace gba {
namespace math {

template <unsigned Exponent>
struct constants {
	static constexpr auto e          = fixed_point<uint32, Exponent>( 2.7182818284590452354 );
	static constexpr auto log2e      = fixed_point<uint32, Exponent>( 1.4426950408889634074 );
	static constexpr auto log10e     = fixed_point<uint32, Exponent>( 0.43429448190325182765 );
	static constexpr auto pi         = fixed_point<uint32, Exponent>( 3.1415926535897932385 );
	static constexpr auto inv_pi     = fixed_point<uint32, Exponent>( 0.31830988618379067154 );
	static constexpr auto inv_sqrtpi = fixed_point<uint32, Exponent>( 0.56418958354775628695 );
	static constexpr auto ln2        = fixed_point<uint32, Exponent>( 0.69314718055994530942 );
	static constexpr auto ln10       = fixed_point<uint32, Exponent>( 2.3025850929940456840 );
	static constexpr auto sqrt2      = fixed_point<uint32, Exponent>( 1.4142135623730950488 );
	static constexpr auto sqrt3      = fixed_point<uint32, Exponent>( 1.7320508075688772935 );
	static constexpr auto inv_sqrt3  = fixed_point<uint32, Exponent>( 0.57735026918962576451 );
	static constexpr auto egmma      = fixed_point<uint32, Exponent>( 0.57721566490153286061 );
	static constexpr auto phi        = fixed_point<uint32, Exponent>( 1.6180339887498948482 );
};

}
}

#endif // define GBAXX_MATH_CONSTANTS_HPP
