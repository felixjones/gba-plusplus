#ifndef GBAXX_INT_TYPE_HPP
#define GBAXX_INT_TYPE_HPP

#include <cstdint>
#include <type_traits>

namespace gba {

template <unsigned int Size, unsigned int Scale = 1>
struct int_type {
	static_assert( Size > 0, "int_type Size cannot be zero" );
	static_assert( Scale > 0, "int_type Scale cannot be zero" );

	static constexpr unsigned int bits = Size * Scale;

	using type = typename std::conditional<bits <= 8, std::int8_t, typename std::conditional<bits <= 16, std::int16_t, typename std::conditional<bits <= 32, std::int32_t, std::int64_t>::type>::type>::type;
	using least = typename std::conditional<bits <= 8, std::int_least8_t, typename std::conditional<bits <= 16, std::int_least16_t, typename std::conditional<bits <= 32, std::int_least32_t, std::int_least64_t>::type>::type>::type;
	using fast = typename std::conditional<bits <= 8, std::int_fast8_t, typename std::conditional<bits <= 16, std::int_fast16_t, typename std::conditional<bits <= 32, std::int_fast32_t, std::int_fast64_t>::type>::type>::type;

	static constexpr typename fast min() {
		return Size == 2 ? -2 : 2 * int_type<bits - 1, 1>::min();
	}

	static constexpr typename fast max() {
		return -min() - 1;
	}

};

template <unsigned int Size, unsigned int Scale = 1, typename = std::enable_if<( Size > 0 )>>
struct uint_type {
	static_assert( Size > 0, "uint_type Size cannot be zero" );
	static_assert( Scale > 0, "uint_type Scale cannot be zero" );

	static constexpr unsigned int bits = Size * Scale;

	using type = typename std::conditional<bits <= 8, std::uint8_t, typename std::conditional<bits <= 16, std::uint16_t, typename std::conditional<bits <= 32, std::uint32_t, std::uint64_t>::type>::type>::type;
	using least = typename std::conditional<bits <= 8, std::uint_least8_t, typename std::conditional<bits <= 16, std::uint_least16_t, typename std::conditional<bits <= 32, std::uint_least32_t, std::uint_least64_t>::type>::type>::type;
	using fast = typename std::conditional<bits <= 8, std::uint_fast8_t, typename std::conditional<bits <= 16, std::uint_fast16_t, typename std::conditional<bits <= 32, std::uint_fast32_t, std::uint_fast64_t>::type>::type>::type;

	static constexpr typename fast min() {
		return 0;
	}

	static constexpr typename fast max() {
		return int_type<Size * Scale + 1>::max();
	}

};

template <unsigned int Size>
using int_size_type = int_type<Size, 8>;

template <unsigned int Size>
using uint_size_type = uint_type<Size, 8>;

} // gba

#endif // define GBAXX_INT_TYPE_HPP
