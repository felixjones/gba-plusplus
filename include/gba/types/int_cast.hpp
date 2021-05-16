#ifndef GBAXX_TYPES_INT_CAST_HPP
#define GBAXX_TYPES_INT_CAST_HPP

#include <gba/types/int_type.hpp>

#if !defined( __has_builtin )
#define __has_builtin( x )  0
#endif

#if __cpp_lib_bit_cast
#include <bit>
#endif

namespace gba {

template <typename Type>
auto int_cast( const Type& value ) noexcept -> typename int_type<sizeof( Type ) * 8>::type {
    using int_type = typename int_type<sizeof( Type ) * 8>::type;
#if __cpp_lib_bit_cast
    return std::bit_cast<int_type>( value );
#elif __has_builtin( __builtin_bit_cast )
    return __builtin_bit_cast( int_type, value );
#else
    return *reinterpret_cast<const int_type *>( &value );
#endif
}

template <typename Type>
auto uint_cast( const Type& value ) noexcept -> typename uint_type<sizeof( Type ) * 8>::type {
    using uint_type = typename uint_type<sizeof( Type ) * 8>::type;
#if __cpp_lib_bit_cast
    return std::bit_cast<uint_type>( value );
#elif __has_builtin( __builtin_bit_cast )
    return __builtin_bit_cast( uint_type, value );
#else
    return *reinterpret_cast<const uint_type *>( &value );
#endif
}

} // gba

#endif // define GBAXX_TYPES_INT_CAST_HPP
