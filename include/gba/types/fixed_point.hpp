#ifndef GBAXX_FIXED_POINT_HPP
#define GBAXX_FIXED_POINT_HPP

#include <limits>
#include <type_traits>

#include <gba/types/int_type.hpp>

namespace gba {

/**
 * @tparam Rep
 * @tparam Exponent
 */
template <class Rep = int32, int Exponent = 0>
class fixed_point {
    static_assert( std::numeric_limits<Rep>::is_integer, "Rep must be integer type" );

private:
    constexpr fixed_point( Rep r, int ) noexcept : m_data( r ) {}

public:
    using rep = Rep;

    constexpr static int exponent = Exponent;
    constexpr static int digits = std::numeric_limits<Rep>::digits;
    constexpr static int integer_digits = digits + exponent;
    constexpr static int fractional_digits = -exponent;

    constexpr fixed_point() noexcept = default;

    template <class FromRep, int FromExponent>
    constexpr fixed_point( const fixed_point<FromRep, FromExponent>& rhs ) noexcept : m_data { fixed_point_to_rep( rhs ) } {}

    template <class Integral, Integral Constant>
    constexpr fixed_point( const std::integral_constant<Integral, Constant>& ) noexcept : fixed_point( fixed_point<Integral, 0>::from_data( Constant ) ) {}

    template <class S>
    constexpr fixed_point( const S& s ) noexcept : fixed_point( fixed_point<S, 0>::from_data( s ) ) {}

    template <class S>
    constexpr fixed_point& operator =( S s ) noexcept {
        return operator =( fixed_point<S, 0>::from_data( s ) );
    }

    template <class FromRep, int FromExponent>
    constexpr fixed_point& operator =( const fixed_point<FromRep, FromExponent>& rhs ) noexcept {
        m_data = fixed_point_to_rep( rhs );
        return *this;
    }

    constexpr operator bool() const noexcept {
        return static_cast<bool>( m_data );
    }

    template <class S, std::enable_if_t<std::numeric_limits<S>::is_integer, int> Dummy = 0>
    constexpr operator S() const noexcept {
        return rep_to_integral<S>( m_data );
    }

    constexpr rep& data() noexcept {
        return m_data;
    }

    constexpr rep data() const noexcept {
        return m_data;
    }

    static constexpr fixed_point from_data( const rep& r ) noexcept {
        return fixed_point( r, 0 );
    }

private:
    template <class FromRep, int FromExponent>
    static constexpr rep fixed_point_to_rep( const fixed_point<FromRep, FromExponent>& rhs ) noexcept;

    template <class S>
    static constexpr S rep_to_integral( rep r ) noexcept;

    rep m_data;

};

namespace detail {

template <class T>
using scale_result_type = decltype( std::declval<T>() * std::declval<T>() );

template <int Exp, class T>
constexpr scale_result_type<T> pow2() noexcept {
    return scale_result_type<T> { 1 } << std::abs( Exp );
}

template <int Exp, class T>
scale_result_type<T> scale2( const T &i ) noexcept {
    return static_cast<scale_result_type<T>>( ( Exp < 0 ) ? static_cast<T>( i ) / pow2<-Exp, T>() : static_cast<T>( i ) * pow2<Exp, T>() );
}

template <int Exp, class Output, class Input>
constexpr Output shift_left( Input i ) noexcept {
    using larger = typename std::conditional<std::numeric_limits<Input>::digits <= std::numeric_limits<Output>::digits, Output, Input>::type;

    return ( Exp > -std::numeric_limits<larger>::digits ) ? static_cast<Output>( scale2<Exp>( static_cast<larger>( i ) ) ) : Output { 0 };
}

} // detail

template <class Rep, int Exponent>
template <class FromRep, int FromExponent>
constexpr typename fixed_point<Rep, Exponent>::rep fixed_point<Rep, Exponent>::fixed_point_to_rep( const fixed_point<FromRep, FromExponent>& rhs ) noexcept {
    return detail::shift_left<FromExponent - Exponent, rep>( rhs.data() );
}

template <class Rep, int Exponent>
template <class S>
constexpr S fixed_point<Rep, Exponent>::rep_to_integral( Rep r ) noexcept {
    static_assert( std::numeric_limits<S>::is_integer, "S must be integral type" );
    return detail::shift_left<Exponent, S>( r );
}

} // gba

#endif // define GBAXX_FIXED_POINT_HPP
