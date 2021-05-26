#ifndef GBAXX_TYPES_MEMMAP_HPP
#define GBAXX_TYPES_MEMMAP_HPP

#include <type_traits>
#include <utility>

#include <gba/types/int_type.hpp>

#if !defined( __has_builtin )
#define __has_builtin( x )  0
#endif

#if __cpp_lib_bit_cast
#include <bit>
#endif

namespace gba {
namespace detail {

template <auto Start, unsigned N, typename D, typename S>
constexpr void constexpr_array_copy( D dst[N], S src[N] ) {
    if constexpr ( Start < N ) {
        constexpr auto index = std::integral_constant<decltype( Start ), Start>();
        dst[index] = src[index];
        constexpr_array_copy<Start + 1, N, D, S>( dst, src );
    }
}

template <typename Type, unsigned Longs = sizeof( Type ) / 4, unsigned Shorts = ( sizeof( Type ) - ( Longs * 4 ) ) / 2, unsigned Bytes = sizeof( Type ) - ( Longs * 4 ) - ( Shorts * 2 )>
struct packed_bit_container;

template <typename Type>
struct packed_bit_container<Type, 0, 0, 1> {
    using type = uint8;
};

template <typename Type>
struct packed_bit_container<Type, 0, 1, 0> {
    using type = uint16;
};

template <typename Type>
struct packed_bit_container<Type, 1, 0, 0> {
    using type = uint32;
};

template <typename Type>
struct packed_bit_container<Type, 0, 1, 1> {
    struct [[gnu::packed]] type {
        void copy( type& d ) const volatile noexcept {
            d.data16 = data16;
            d.data8 = data8;
        }

        void move( type&& d ) volatile noexcept {
            data16 = d.data16;
            data8 = d.data8;
        }

        uint16 data16;
        uint8 data8;
    };
};

template <typename Type, unsigned Longs>
struct packed_bit_container<Type, Longs, 0, 1> {
    struct [[gnu::packed]] type {
        void copy( type& d ) const volatile noexcept {
            constexpr_array_copy<0, Longs>( d.data32, data32 );
            d.data8 = data8;
        }

        void move( type&& d ) volatile noexcept {
            constexpr_array_copy<0, Longs>( data32, d.data32 );
            data8 = d.data8;
        }

        uint32 data32[Longs];
        uint8 data8;
    };
};

template <typename Type, unsigned Longs>
struct packed_bit_container<Type, Longs, 1, 0> {
    struct [[gnu::packed]] type {
        void copy( type& d ) const volatile noexcept {
            constexpr_array_copy<0, Longs>( d.data32, data32 );
            d.data16 = data16;
        }

        void move( type&& d ) volatile noexcept {
            constexpr_array_copy<0, Longs>( data32, d.data32 );
            data16 = d.data16;
        }

        uint32 data32[Longs];
        uint16 data16;
    };
};

template <typename Type, unsigned Longs>
struct packed_bit_container<Type, Longs, 1, 1> {
    struct [[gnu::packed]] type {
        void copy( type& d ) const volatile noexcept {
            constexpr_array_copy<0, Longs>( d.data32, data32 );
            d.data16 = data16;
            d.data8 = data8;
        }

        void move( type&& d ) volatile noexcept {
            constexpr_array_copy<0, Longs>( data32, d.data32 );
            data16 = d.data16;
            data8 = d.data8;
        }

        uint32 data32[Longs];
        uint16 data16;
        uint8 data8;
    };
};

template <typename Type, unsigned Longs>
struct packed_bit_container<Type, Longs, 0, 0> {
    struct type {
        void copy( type& d ) const volatile noexcept {
            constexpr_array_copy<0, Longs>( d.data32, data32 );
        }

        void move( type&& d ) volatile noexcept {
            constexpr_array_copy<0, Longs>( data32, d.data32 );
        }

        uint32 data32[Longs];
    };
};

template <typename Type, typename Enable = void>
struct volatile_op;

template <typename Type>
struct volatile_op<Type, typename std::enable_if<std::is_fundamental<Type>::value>::type> {
    static void copy( Type& d, const volatile Type * const t ) noexcept {
        d = Type( *t );
    }

    static void move( volatile Type * const d, Type&& t ) noexcept {
        *d = t;
    }
};

template <typename Type>
struct volatile_op<Type, typename std::enable_if<!std::is_fundamental<Type>::value>::type> {
    static void copy( Type& d, const volatile Type * const t ) noexcept {
        t->copy( d );
    }

    static void move( volatile Type * const d, Type&& t ) noexcept {
        d->move( std::move( t ) );
    }
};

} // detail

template <typename Type, unsigned Address>
class memmap {
public:
    using type = Type;
    static constexpr auto address = Address;
};

template <typename Type, unsigned Address>
class imemmap : public memmap<Type, Address> {
public:
    using type = typename memmap<Type, Address>::type;
    static constexpr auto address = memmap<Type, Address>::address;

    [[nodiscard]]
    static inline type read() noexcept {
        if constexpr ( std::is_fundamental<type>::value ) {
            return *reinterpret_cast<const volatile type *>( address );
        } else if constexpr ( std::is_trivially_copyable<type>::value ) {
            using bit_type = typename detail::packed_bit_container<type>::type;
            bit_type value;
            detail::volatile_op<bit_type>::copy( value, reinterpret_cast<const volatile bit_type *>( address ) );
#if __cpp_lib_bit_cast
            return std::bit_cast<type>( value );
#elif __has_builtin( __builtin_bit_cast )
            return __builtin_bit_cast( type, value );
#else
            return *reinterpret_cast<const type *>( &value );
#endif
        } else {
            static_assert( !std::is_same<type, type>::value, "Type incompatible with imemmap" );
        }
        __builtin_unreachable();
    }
};

template <typename Type, unsigned Address>
class omemmap : public memmap<Type, Address> {
public:
    using type = typename memmap<Type, Address>::type;
    static constexpr auto address = memmap<Type, Address>::address;

    static inline void write( type&& value ) noexcept {
        if constexpr ( std::is_fundamental<type>::value ) {
            *reinterpret_cast<volatile type *>( address ) = value;
        } else if constexpr ( std::is_trivially_copyable<type>::value ) {
            using bit_type = typename detail::packed_bit_container<type>::type;
#if __cpp_lib_bit_cast
            auto asBitType = std::bit_cast<bit_type>( value );
#elif __has_builtin( __builtin_bit_cast )
            auto asBitType = __builtin_bit_cast( bit_type, value );
#else
            bit_type asBitType;
            if constexpr ( std::is_trivially_move_constructible<type>::value ) {
                new ( &asBitType ) type { std::move( value ) };
            } else {
                asBitType = *reinterpret_cast<const bit_type *>( &value );
            }
#endif
            detail::volatile_op<bit_type>::move( reinterpret_cast<volatile bit_type *>( address ), std::move( asBitType ) );
        } else if constexpr ( std::is_trivially_move_constructible<type>::value ) {
            using bit_type = typename detail::packed_bit_container<type>::type;
            bit_type asBitType;
            new ( &asBitType ) type { std::move( value ) };
            detail::volatile_op<bit_type>::move( reinterpret_cast<volatile bit_type *>( address ), std::move( asBitType ) );
        } else {
            static_assert( !std::is_same<type, type>::value, "Type incompatible with omemmap" );
        }
    }

    static inline void write( const type& value ) noexcept {
        if constexpr ( std::is_fundamental<type>::value ) {
            *reinterpret_cast<volatile type *>( address ) = value;
        } else if constexpr ( std::is_trivially_copyable<type>::value ) {
            using bit_type = typename detail::packed_bit_container<type>::type;
#if __cpp_lib_bit_cast
            auto asBitType = std::bit_cast<bit_type>( value );
#elif __has_builtin( __builtin_bit_cast )
            auto asBitType = __builtin_bit_cast( bit_type, value );
#else
            bit_type asBitType;
            if constexpr ( std::is_trivially_move_constructible<type>::value ) {
                new ( &asBitType ) type { value };
            } else {
                asBitType = *reinterpret_cast<const bit_type *>( &value );
            }

#endif
            detail::volatile_op<bit_type>::move( reinterpret_cast<volatile bit_type *>( address ), std::move( asBitType ) );
        } else if constexpr ( std::is_trivially_move_constructible<type>::value ) {
            using bit_type = typename detail::packed_bit_container<type>::type;
            bit_type asBitType;
            new ( &asBitType ) type { value };
            detail::volatile_op<bit_type>::move( reinterpret_cast<volatile bit_type *>( address ), std::move( asBitType ) );
        } else {
            static_assert( !std::is_same<type, type>::value, "Type incompatible with omemmap" );
        }
    }

    template <typename... Args>
    static inline void emplace( Args&&... args ) noexcept {
        if constexpr ( std::is_fundamental<type>::value ) {
            *reinterpret_cast<volatile type *>( address ) = type { std::forward<Args>( args )... };
        } else if constexpr ( std::is_trivially_default_constructible<type>::value || std::is_constructible<type, Args...>::value ) {
            using bit_type = typename detail::packed_bit_container<type>::type;
            bit_type asBitType;
            new ( &asBitType ) type { std::forward<Args>( args )... };
            detail::volatile_op<bit_type>::move( reinterpret_cast<volatile bit_type *>( address ), std::move( asBitType ) );
        } else {
            static_assert( !std::is_same<type, type>::value, "Type incompatible with omemmap" );
        }
    }
};

template <typename Type, unsigned Address>
class iomemmap : public imemmap<Type, Address>, public omemmap<Type, Address> {
public:
    using type = typename memmap<Type, Address>::type;
    static constexpr auto address = memmap<Type, Address>::address;
};

} // gba

#endif // define GBAXX_TYPES_MEMMAP_HPP
