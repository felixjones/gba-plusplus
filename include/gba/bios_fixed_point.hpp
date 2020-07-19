#ifndef GBAXX_BIOS_FIXED_POINT_HPP
#define GBAXX_BIOS_FIXED_POINT_HPP

#include <gba/bios_asm.hpp>
#include <gba/int.hpp>
#include <gba/fixed_point.hpp>
#include <gba/math_constants.hpp>

namespace gba {
namespace bios {

/// @ingroup bios_math
/// @brief Returns the fixed-point square root of x
/// @param x gba::fixed_point
/// @return square root of x
template <typename ReprType, unsigned ExpBits>
[[gnu::const]]
auto sqrt( const fixed_point<ReprType, ExpBits>& x ) noexcept {
	using exp_even_type = fixed_point<uint32, ExpBits - ( ExpBits % 2 )>;
	using exp_half_type = fixed_point<uint32, exp_even_type::exponent / 2>;

	const auto resultData = swi::sqrt( exp_even_type( x ).data() );
	const auto resultFixed = exp_half_type::from_data( resultData );
	return fixed_point<ReprType, ExpBits>( resultFixed );
}

/// @ingroup bios_math
/// @brief Returns the principal value of the arc tangent of x, expressed in radians
/// @param x gba::fixed_point
/// @return arctan of x
template <typename ReprType, unsigned ExpBits>
[[gnu::const]]
auto arc_tan( const fixed_point<ReprType, ExpBits>& x ) noexcept -> typename std::enable_if<std::is_signed<ReprType>::value, fixed_point<ReprType, ExpBits>>::type {
	using fixed_type = fixed_point<ReprType, ExpBits>;
	using fixed14_type = fixed_point<int32, 14>;

	constexpr auto halfPi = math::constants<fixed14_type::exponent>::pi / 2;

	const auto resultData = swi::arc_tan( fixed14_type( x ).data() );
	const auto resultFixed = fixed14_type::from_data( resultData ); // -1 .. 1
	return static_cast<fixed_type>( resultFixed * halfPi ); // -pi/2 .. +pi/2
}

/// @ingroup bios_math
/// @brief Computes the arc tangent of y/x using the signs of arguments to determine the correct quadrant
/// @param x gba::fixed_point (signed)
/// @param y gba::fixed_point (signed)
/// @return promoted fixed_point between -pi and +pi
template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits, typename = typename std::enable_if<std::is_signed<LhsReprType>::value && std::is_signed<RhsReprType>::value, void>::type>
[[gnu::const]]
auto arc_tan2( const fixed_point<LhsReprType, LhsExpBits>& x, const fixed_point<RhsReprType, RhsExpBits>& y ) noexcept {
	using repr_type = promote::integer<LhsReprType, RhsReprType>;

	constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits );

	using fixed14_type = fixed_point<repr_type, 14>;
	using fixed15_type = fixed_point<int16, 15>;
	using fixed_type = fixed_point<repr_type, exponent>;

	constexpr auto pi = math::constants<fixed15_type::exponent>::pi;

	const auto a = fixed14_type( x ).data();
	const auto b = fixed14_type( y ).data();
	const auto resultData = swi::arc_tan2( a, b );
	const auto resultFixed = fixed15_type::from_data( resultData ); // -1..+1
	return static_cast<fixed_type>( resultFixed * pi ); // -pi..+pi
}

} // bios
} // gba

#endif // define GBAXX_BIOS_FIXED_POINT_HPP
