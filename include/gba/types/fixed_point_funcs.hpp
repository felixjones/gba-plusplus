#ifndef GBAXX_FIXED_POINT_FUNCS_HPP
#define GBAXX_FIXED_POINT_FUNCS_HPP

#if !defined( __has_builtin )
#define __has_builtin( x )  0
#endif

#if __cpp_lib_is_constant_evaluated
#include <type_traits>
#endif

#if __cpp_lib_is_constant_evaluated
#define gbaxx_fixed_point_funcs_constant( x )   std::is_constant_evaluated()
#elif __has_builtin( __builtin_is_constant_evaluated  )
#define gbaxx_fixed_point_funcs_constant( x )   __builtin_is_constant_evaluated()
#elif __has_builtin( __builtin_constant_p )
#define gbaxx_fixed_point_funcs_constant( x )   __builtin_constant_p( x )
#else
#define gbaxx_fixed_point_funcs_constant
#endif

#include <algorithm>

#include <gba/bios/affine.hpp>
#include <gba/bios/math.hpp>
#include <gba/types/fixed_point.hpp>
#include <gba/types/fixed_point_make.hpp>
#include <gba/types/fixed_point_operators.hpp>

#if defined( __agb_abi )
#include <gba/ext/agbabi.hpp>
#endif

namespace gba {
namespace detail {

constexpr auto sin_bam16( int32 x ) noexcept {
#if defined( __agb_abi )
    if ( gbaxx_fixed_point_funcs_constant( x ) == false ) {
        return agbabi::sin( x );
    }
#endif
    x = static_cast<uint32>( x ) << 17;
    if ( static_cast<int32>( x ^ ( static_cast<uint32>( x ) << 1 ) ) < 0 ) {
        x = 0x80000000 - static_cast<uint32>( x );
    }
    x = x >> 17;
    return make_fixed<2, 29>::from_data( x * ( ( 3 << 15 ) - ( x * x >> 11 ) ) );
}

template <class Rep, int Exponent>
constexpr int32 radian_to_bam16( const fixed_point<Rep, Exponent>& radian ) noexcept {
    constexpr auto radTo16 = make_fixed<13, 18>( 16384.0 / 3.14159265358979323846264338327950288 );
    return static_cast<int32>( radian * radTo16 );
}

template <class Rep, int Exponent>
constexpr uint32 radian_to_ubam16( const fixed_point<Rep, Exponent>& radian ) noexcept {
    constexpr auto radTo16 = make_ufixed<14, 18>( ( 16384.0 * 2.0 ) / 3.14159265358979323846264338327950288 );
    return static_cast<uint32>( radian * radTo16 );
}

template <class Rep>
constexpr Rep sqrt_bit( Rep n, Rep bit ) noexcept {
    if ( bit > n ) {
        return sqrt_bit<Rep>( n, bit >> 2 );
    } else {
        return bit;
    }
}

template <class Rep>
constexpr auto sqrt_bit( Rep n ) noexcept {
    return sqrt_bit<Rep>( n, Rep( 1 ) << ( sizeof( Rep ) * 8 - 2 ) );
}

template <class Rep>
constexpr Rep sqrt_solve3( Rep n, Rep bit, Rep result ) noexcept {
    if ( bit != 0 ) {
        if ( n >= result + bit ) {
            return sqrt_solve3<Rep>( static_cast<Rep>( n - ( result + bit ) ), bit >> 2, static_cast<Rep>( ( result >> 1 ) + bit ) );
        } else {
            return sqrt_solve3<Rep>( n, bit >> 2, result >> 1 );
        }
    } else {
        return result;
    }
}

template <class Rep>
constexpr auto sqrt_solve1( Rep n ) noexcept {
    return sqrt_solve3<Rep>( n, sqrt_bit<Rep>( n ), 0 );
}

} // detail

template <class Rep, int Exponent>
constexpr auto sqrt( const fixed_point<Rep, Exponent>& x ) noexcept {
    constexpr auto larger_exponent = ( Exponent - ( Exponent % 2 ) ) - ( std::numeric_limits<uint32>::digits - std::numeric_limits<typename std::make_unsigned<Rep>::type>::digits );

    if ( gbaxx_fixed_point_funcs_constant( x.data() ) ) {
        return fixed_point<uint16, larger_exponent / 2>::from_data( detail::sqrt_solve1( fixed_point<uint32, larger_exponent>( x ).data() ) );
    }

    return fixed_point<uint16, larger_exponent / 2>::from_data( bios::sqrt( fixed_point<uint32, larger_exponent>( x ).data() ) );
}

template <class Rep, int Exponent>
constexpr auto sin( const fixed_point<Rep, Exponent>& radian ) noexcept {
    return detail::sin_bam16( detail::radian_to_bam16( radian ) );
}

template <class Rep, int Exponent>
constexpr auto cos( const fixed_point<Rep, Exponent>& radian ) noexcept {
    return detail::sin_bam16( detail::radian_to_bam16( radian ) + 0x2000 );
}

using cosine_type = object::mat2::column0_type::value_type;

template <class Rep, int Exponent>
constexpr std::tuple<cosine_type, cosine_type> cosine( const fixed_point<Rep, Exponent>& radian ) noexcept {
    if ( gbaxx_fixed_point_funcs_constant( radian.data() ) ) {
        return std::make_tuple( cos( radian ), sin( radian ) );
    } else {
        bios::obj_affine_input i {
                1, 1,
                make_ufixed<8, 8>::from_data( detail::radian_to_ubam16( radian ) )
        };
        object::mat2 m; // NOLINT(cppcoreguidelines-pro-type-member-init)
        bios::obj_affine_set( &i, &m, 1, 2 );
        return std::make_tuple( m.column0.x, m.column1.x );
    }
}

template <class Rep, int Exponent>
constexpr auto nextafter( const fixed_point<Rep, Exponent>& from, const fixed_point<Rep, Exponent>& to ) noexcept {
    if ( from < to ) {
        return fixed_point<Rep, Exponent>::from_data( from.data() + 1 );
    } else if ( from > to ) {
        return fixed_point<Rep, Exponent>::from_data( from.data() - 1 );
    }

    return from;
}

template <class LhsRep, int LhsExponent, class RhsRep, int RhsExponent>
constexpr auto nexttoward( const fixed_point<LhsRep, LhsExponent>& from, const fixed_point<RhsRep, RhsExponent>& to ) noexcept {
    if ( from < to ) {
        return fixed_point<LhsRep, LhsExponent>::from_data( from.data() + 1 );
    } else if ( from > to ) {
        return fixed_point<LhsRep, LhsExponent>::from_data( from.data() - 1 );
    }

    return from;
}

} // gba

#endif // define GBAXX_FIXED_POINT_FUNCS_HPP
