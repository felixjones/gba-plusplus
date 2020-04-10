#ifndef GBAXX_TYPE_PROMOTION_HPP
#define GBAXX_TYPE_PROMOTION_HPP

#include <type_traits>

#include <gba/int_type.hpp>

namespace gba {
namespace promote {

template <typename T>
using make_wider = typename std::conditional<std::is_signed<T>::value, typename int_sized_type<sizeof( T ) + 1>::type, typename uint_sized_type<sizeof( T ) + 1>::type>::type;

template <typename From, typename To>
using copy_sign = typename std::conditional<std::is_signed<From>::value, typename std::make_signed<To>::type, typename std::make_unsigned<To>::type>::type;

template <typename Lhs, typename Rhs>
using integer =
	typename std::conditional<std::is_signed<Lhs>::value || std::is_signed<Rhs>::value,
		typename std::make_signed<typename std::conditional<sizeof( Lhs ) >= sizeof( Rhs ), Lhs, Rhs>::type>::type,
		typename std::make_unsigned<typename std::conditional<sizeof( Lhs ) >= sizeof( Rhs ), Lhs, Rhs>::type>::type
	>::type;

} // promote
} // gba

#endif // define GBAXX_TYPE_PROMOTION_HPP
