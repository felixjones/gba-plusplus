#ifndef GBAXX_INT_TYPE_HPP
#define GBAXX_INT_TYPE_HPP

#include <cstdint>
#include <type_traits>

namespace gba {

template <unsigned int Size>
struct int_type {
	using type = typename std::conditional<Size <= 1, std::int8_t, typename std::conditional<Size <= 2, std::int16_t, typename std::conditional<Size <= 4, std::int32_t, std::int64_t>::type>::type>::type;
	using least = typename std::conditional<Size <= 1, std::int_least8_t, typename std::conditional<Size <= 2, std::int_least16_t, typename std::conditional<Size <= 4, std::int_least32_t, std::int_least64_t>::type>::type>::type;
	using fast = typename std::conditional<Size <= 1, std::int_fast8_t, typename std::conditional<Size <= 2, std::int_fast16_t, typename std::conditional<Size <= 4, std::int_fast32_t, std::int_fast64_t>::type>::type>::type;
};

template <unsigned int Size>
struct uint_type {
	using type = typename std::conditional<Size <= 1, std::uint8_t, typename std::conditional<Size <= 2, std::uint16_t, typename std::conditional<Size <= 4, std::uint32_t, std::uint64_t>::type>::type>::type;
	using least = typename std::conditional<Size <= 1, std::uint_least8_t, typename std::conditional<Size <= 2, std::uint_least16_t, typename std::conditional<Size <= 4, std::uint_least32_t, std::uint_least64_t>::type>::type>::type;
	using fast = typename std::conditional<Size <= 1, std::uint_fast8_t, typename std::conditional<Size <= 2, std::uint_fast16_t, typename std::conditional<Size <= 4, std::uint_fast32_t, std::uint_fast64_t>::type>::type>::type;
};

} // gba

#endif // define GBAXX_INT_TYPE_HPP
