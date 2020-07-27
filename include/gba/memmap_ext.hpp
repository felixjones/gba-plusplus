#ifndef GBAXX_MEMMAP_EXT_HPP
#define GBAXX_MEMMAP_EXT_HPP

#include <gba/int.hpp>
#include <gba/memmap.hpp>

namespace gba {
namespace detail {

    template <unsigned Size>
    union packed_uint {
        static constexpr auto size = Size;

        static constexpr auto num_ints = size / 4;
        static constexpr auto num_shorts = ( size - ( num_ints * 4 ) ) / 2;
        static constexpr auto num_bytes = size - ( num_shorts * 2 + num_ints * 4 );

        static constexpr auto start_shorts = num_ints * 2;
        static constexpr auto start_bytes = ( start_shorts + num_shorts ) * 2;

        static constexpr auto end_ints = num_ints;
        static constexpr auto end_shorts = start_shorts + num_shorts;
        static constexpr auto end_bytes = start_bytes + num_bytes;
    };

} // detail

// Read only memory mapped
template <typename Type, unsigned Address>
class imemmap<Type, Address, typename std::enable_if<!detail::converts_to_uint<Type>::value>::type> : public virtual memmap<Type, Address> {
private:
    using uint_type = detail::packed_uint<sizeof( Type )>;

public:
    static Type read() noexcept {
        uint8 data[uint_type::size] {};

        for ( unsigned ii = 0; ii < uint_type::end_ints; ++ii ) {
            const uint32 d32 = *( volatile const uint32 * )( Address + ii * sizeof( uint32 ) );
            std::memcpy( &data[ii * 4], &d32, sizeof( uint32 ) );
        }

        for ( unsigned ii = uint_type::start_shorts; ii < uint_type::end_shorts; ++ii ) {
            const uint16 d16 = *( volatile const uint16 * )( Address + ii * sizeof( uint16 ) );
            std::memcpy( &data[ii * 2], &d16, sizeof( uint16 ) );
        }

        for ( unsigned ii = uint_type::start_bytes; ii < uint_type::end_bytes; ++ii ) {
            const uint8 d8 = *( volatile const uint8 * )( Address + ii );
            std::memcpy( &data[ii], &d8, sizeof( uint8 ) );
        }

        Type value {};
        std::memcpy( &value, &data[0], sizeof( Type ) );
        return value;
    }
};

// Write only memory mapped
template <typename Type, unsigned Address>
class omemmap<Type, Address, typename std::enable_if<!detail::converts_to_uint<Type>::value>::type> : public virtual memmap<Type, Address> {
private:
    using uint_type = detail::packed_uint<sizeof( Type )>;

public:
    static void write( const Type& value ) noexcept {
        const auto vp = &value;

        const uint8 * data8 {};
        const uint16 * data16 {};
        const uint32 * data32 {};

        std::memcpy( &data8, &vp, sizeof( data8 ) );
        std::memcpy( &data16, &vp, sizeof( data16 ) );
        std::memcpy( &data32, &vp, sizeof( data32 ) );

        for ( unsigned ii = 0; ii < uint_type::end_ints; ++ii ) {
            *( volatile uint32 * )( Address + ii * sizeof( uint32 ) ) = data32[ii];
        }

        for ( unsigned ii = uint_type::start_shorts; ii < uint_type::end_shorts; ++ii ) {
            *( volatile uint16 * )( Address + ii * sizeof( uint16 ) ) = data16[ii];
        }

        for ( unsigned ii = uint_type::start_bytes; ii < uint_type::end_bytes; ++ii ) {
            *( volatile uint8 * )( Address + ii ) = data8[ii];
        }
    }
};

} // gba

#endif // define GBAXX_MEMMAP_EXT_HPP
