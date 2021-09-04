#ifndef GBAXX_FIXED_POINT_MAKE_HPP
#define GBAXX_FIXED_POINT_MAKE_HPP

#include <limits>
#include <type_traits>

#include <gba/types/fixed_point.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace detail {

    template <class T, int Digits, class Enable = void>
    struct set_digits;

    template <class T, int Digits>
    struct set_digits<T, Digits, std::enable_if_t<std::is_integral<T>::value>> : detail::set_digits_integer<T, Digits> {};

} // detail

template <int IntegerDigits, int FractionalDigits = 0, class Narrowest = signed>
using make_fixed = fixed_point<typename detail::set_digits<Narrowest, IntegerDigits + FractionalDigits>::type, -FractionalDigits>;

template <int IntegerDigits, int FractionalDigits = 0, class Narrowest = unsigned>
using make_ufixed = make_fixed<IntegerDigits, FractionalDigits, typename std::make_unsigned<Narrowest>::type>;

} // gba

#endif // define GBAXX_FIXED_POINT_MAKE_HPP
