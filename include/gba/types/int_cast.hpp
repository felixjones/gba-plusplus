#ifndef GBAXX_TYPES_INT_CAST_HPP
#define GBAXX_TYPES_INT_CAST_HPP

#include <gba/types/int_type.hpp>

#if !defined( __has_builtin )
#define __has_builtin( x )  0
#endif

#if __cpp_lib_bit_cast
#include <bit>
#endif

#if __cpp_lib_bit_cast || __has_builtin( __builtin_bit_cast )
#define gbaxx_int_cast_constexpr constexpr
#else
#include <cstring>
#define gbaxx_int_cast_constexpr
#endif

namespace gba {

template <typename Type>
gbaxx_int_cast_constexpr auto int_cast( const Type& value ) noexcept -> typename std::enable_if_t<sizeof( Type ) && std::is_trivially_copyable_v<Type>, typename int_type<sizeof( Type ) * 8>::type> {
    using int_type = typename int_type<sizeof( Type ) * 8>::type;
#if __cpp_lib_bit_cast
    return std::bit_cast<int_type>( value );
#elif __has_builtin( __builtin_bit_cast )
    return __builtin_bit_cast( int_type, value );
#else
    int_type dst;
    std::memcpy( &dst, &value, sizeof( int_type ) );
    return dst;
#endif
}

template <typename Type>
gbaxx_int_cast_constexpr auto uint_cast( const Type& value ) noexcept -> typename std::enable_if_t<sizeof( Type ) && std::is_trivially_copyable_v<Type>, typename uint_type<sizeof( Type ) * 8>::type> {
    using uint_type = typename uint_type<sizeof( Type ) * 8>::type;
#if __cpp_lib_bit_cast
    return std::bit_cast<uint_type>( value );
#elif __has_builtin( __builtin_bit_cast )
    return __builtin_bit_cast( uint_type, value );
#else
    uint_type dst;
    std::memcpy( &dst, &value, sizeof( uint_type ) );
    return dst;
#endif
}

} // gba

#undef gbaxx_int_cast_constexpr

#endif // define GBAXX_TYPES_INT_CAST_HPP
