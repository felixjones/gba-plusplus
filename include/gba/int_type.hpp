#ifndef GBAXX_INT_TYPE_HPP
#define GBAXX_INT_TYPE_HPP

#include <cstdint>
#include <type_traits>

namespace gba {

template <unsigned int Bits>
struct int_type {
	static_assert( Bits > 1, "int_type Bits cannot be less than two" );

	using type = typename std::conditional<Bits <= 8, std::int8_t, typename std::conditional<Bits <= 16, std::int16_t, typename std::conditional<Bits <= 32, std::int32_t, std::int64_t>::type>::type>::type;
	using least = typename std::conditional<Bits <= 8, std::int_least8_t, typename std::conditional<Bits <= 16, std::int_least16_t, typename std::conditional<Bits <= 32, std::int_least32_t, std::int_least64_t>::type>::type>::type;
	using fast = typename std::conditional<Bits <= 8, std::int_fast8_t, typename std::conditional<Bits <= 16, std::int_fast16_t, typename std::conditional<Bits <= 32, std::int_fast32_t, std::int_fast64_t>::type>::type>::type;

	static constexpr fast min() {
		return Bits == 2 ? -2 : 2 * int_type<Bits - 1>::min();
	}

	static constexpr fast max() {
		return -min() - 1;
	}

};

template <unsigned int Bits>
struct uint_type {
	static_assert( Bits > 0, "uint_type Bits cannot be zero" );

	using type = typename std::conditional<Bits <= 8, std::uint8_t, typename std::conditional<Bits <= 16, std::uint16_t, typename std::conditional<Bits <= 32, std::uint32_t, std::uint64_t>::type>::type>::type;
	using least = typename std::conditional<Bits <= 8, std::uint_least8_t, typename std::conditional<Bits <= 16, std::uint_least16_t, typename std::conditional<Bits <= 32, std::uint_least32_t, std::uint_least64_t>::type>::type>::type;
	using fast = typename std::conditional<Bits <= 8, std::uint_fast8_t, typename std::conditional<Bits <= 16, std::uint_fast16_t, typename std::conditional<Bits <= 32, std::uint_fast32_t, std::uint_fast64_t>::type>::type>::type;

	static constexpr fast min() {
		return 0;
	}

	static constexpr fast max() {
		return int_type<Bits + 1>::max();
	}

};

template <unsigned int Size>
using int_sized_type = int_type<Size * 8>;

template <unsigned int Size>
using uint_sized_type = uint_type<Size * 8>;

} // gba

#endif // define GBAXX_INT_TYPE_HPP
