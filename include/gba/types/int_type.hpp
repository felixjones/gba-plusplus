#ifndef GBAXX_TYPES_INT_TYPE_HPP
#define GBAXX_TYPES_INT_TYPE_HPP

#include <cstdint>
#include <limits>
#include <type_traits>

namespace gba {

/**
 * Signed integer types
 * @tparam Bits minimum size of this integer type in bits
 */
template <unsigned Bits>
struct int_type {
    static_assert( Bits > 0, "int_type Bits cannot be zero" );

    /// Exact-width integer type
    using type = typename std::conditional<Bits <= 8, std::int8_t, typename std::conditional<Bits <= 16, std::int16_t, typename std::conditional<Bits <= 32, std::int32_t, std::int64_t>::type>::type>::type;
    /// Minimum-width integer type
    using least = typename std::conditional<Bits <= 8, std::int_least8_t, typename std::conditional<Bits <= 16, std::int_least16_t, typename std::conditional<Bits <= 32, std::int_least32_t, std::int_least64_t>::type>::type>::type;
    /// Fastest minimum-width integer type
    using fast = typename std::conditional<Bits <= 8, std::int_fast8_t, typename std::conditional<Bits <= 16, std::int_fast16_t, typename std::conditional<Bits <= 32, std::int_fast32_t, std::int_fast64_t>::type>::type>::type;

    /**
     * Smallest possible value to be stored in this type
     * @return -(2^(Bits-1))
     */
    static constexpr auto min() noexcept {
        return -( 1 << ( Bits - 1 ) );
    }

    /**
     * Largest possible value to be stored in this type
     * @return (2^(Bits-1))-1
     */
    static constexpr auto max() noexcept {
        return ( 1 << ( Bits - 1 ) ) - 1;
    }
};

/**
 * Unsigned integer types
 * @tparam Bits minimum size of this integer type in bits
 */
template <unsigned int Bits>
struct uint_type {
    static_assert( Bits > 0, "uint_type Bits cannot be zero" );

    /// Exact-width integer type
    using type = typename std::conditional<Bits <= 8, std::uint8_t, typename std::conditional<Bits <= 16, std::uint16_t, typename std::conditional<Bits <= 32, std::uint32_t, std::uint64_t>::type>::type>::type;
    /// Minimum-width integer type
    using least = typename std::conditional<Bits <= 8, std::uint_least8_t, typename std::conditional<Bits <= 16, std::uint_least16_t, typename std::conditional<Bits <= 32, std::uint_least32_t, std::uint_least64_t>::type>::type>::type;
    /// Fastest minimum-width integer type
    using fast = typename std::conditional<Bits <= 8, std::uint_fast8_t, typename std::conditional<Bits <= 16, std::uint_fast16_t, typename std::conditional<Bits <= 32, std::uint_fast32_t, std::uint_fast64_t>::type>::type>::type;

    /**
     * Smallest possible value to be stored in this type
     * @return 0
     */
    static constexpr auto min() noexcept {
        return 0;
    }

    /**
     * Largest possible value to be stored in this type
     * @return (2^Bits)-1
     */
    static constexpr auto max() noexcept {
        return ( 1 << Bits ) - 1;
    }
};

/// 8-bit signed type
using int8 = int_type<8>::type;
/// 16-bit signed type
using int16 = int_type<16>::type;
/// 32-bit signed type
using int32 = int_type<32>::type;

/// 8-bit unsigned type
using uint8 = uint_type<8>::type;
/// 16-bit unsigned type
using uint16 = uint_type<16>::type;
/// 32-bit unsigned type
using uint32 = uint_type<32>::type;

namespace detail {

    template <int MinNumDigits, class Smaller, class T>
    struct enable_for_range : std::enable_if<MinNumDigits <= std::numeric_limits<T>::digits && std::numeric_limits<Smaller>::digits < MinNumDigits> {};

    template <int MinNumDigits, class Smallest>
    struct enable_for_range<MinNumDigits, void, Smallest> : std::enable_if<MinNumDigits <= std::numeric_limits<Smallest>::digits> {};

    template <int MinNumDigits, class Enable = void>
    struct set_digits_signed;

    template <int MinNumDigits>
    struct set_digits_signed<MinNumDigits, typename detail::enable_for_range<MinNumDigits, void, std::int8_t>::type> {
        using type = int8;
    };

    template <int MinNumDigits>
    struct set_digits_signed<MinNumDigits, typename detail::enable_for_range<MinNumDigits, std::int8_t, std::int16_t>::type> {
        using type = int16;
    };

    template <int MinNumDigits>
    struct set_digits_signed<MinNumDigits, typename detail::enable_for_range<MinNumDigits, std::int16_t, std::int32_t>::type> {
        using type = int32;
    };

    template <int MinNumDigits, class Enable = void>
    struct set_digits_unsigned;

    template <int MinNumDigits>
    struct set_digits_unsigned<MinNumDigits, typename detail::enable_for_range<MinNumDigits, void, std::uint8_t>::type> {
        using type = uint8;
    };

    template <int MinNumDigits>
    struct set_digits_unsigned<MinNumDigits, typename detail::enable_for_range<MinNumDigits, std::uint8_t, std::uint16_t>::type> {
        using type = uint16;
    };

    template <int MinNumDigits>
    struct set_digits_unsigned<MinNumDigits, typename detail::enable_for_range<MinNumDigits, std::uint16_t, std::uint32_t>::type> {
        using type = uint32;
    };

    template <class Integer, int MinNumDigits>
    using set_digits_integer = std::conditional_t<std::numeric_limits<Integer>::is_signed, set_digits_signed<MinNumDigits>, set_digits_unsigned<MinNumDigits>>;

} // detail
} // gba

#endif // define GBAXX_TYPES_INT_TYPE_HPP
