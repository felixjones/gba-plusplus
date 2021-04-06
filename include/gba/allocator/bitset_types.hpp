#ifndef GBAXX_ALLOCATOR_BITSET_TYPES_HPP
#define GBAXX_ALLOCATOR_BITSET_TYPES_HPP

#include <algorithm>

#include <gba/allocator/buffer.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace allocator {

class bitset_access {
public:
    static constexpr auto buffer_mask( const buffer& buffer ) noexcept {
        return ~( ( ( 1u << buffer.m_width ) - 1u ) << buffer.m_x );
    }

    static constexpr auto buffer_height( const buffer& buffer ) noexcept {
        return buffer.m_height;
    }

    static constexpr auto buffer_y( const buffer& buffer ) noexcept {
        return buffer.m_y;
    }
};

class simple_bitset : public bitset_access {
protected:
    constexpr void unset( buffer& buffer ) noexcept {
        m_bitset &= buffer_mask( buffer );
    }

    constexpr uint32 bitset_find_free( const int bits, uint32& shift ) const noexcept {
        uint32 mask = ( 1u << bits ) - 1u;
        while ( shift <= ( 32u - bits ) && m_bitset & mask ) {
            shift += 1;
            mask <<= 1;
        }

        if ( shift <= ( 32u - bits ) ) {
            return mask;
        }

        return 0;
    }

    template <int Alignment>
    constexpr uint32 bitset_find_free_aligned( const int bits, uint32& shift ) const noexcept {
        const uint32 alignedShifts = std::max( 0, Alignment - bits );
        uint32 mask = ( 1u << bits ) - 1u;

        uint32 subshift = 0;
        while ( subshift < ( 32u - bits ) ) {
            while ( ( shift - subshift ) <= alignedShifts && m_bitset & mask ) {
                mask <<= 1;
                shift += 1;
            }

            if ( ( shift - subshift ) <= alignedShifts ) {
                return mask;
            }

            mask <<= ( Alignment - alignedShifts - 1 );
            shift += ( Alignment - alignedShifts - 1 );
            subshift += Alignment;
        }

        return 0;
    }

    uint32 m_bitset;
};

template <unsigned Pages>
class bitset_2d : public bitset_access {
protected:
    constexpr void unset( buffer& buffer ) noexcept {
        const auto mask = buffer_mask( buffer );
        for ( int ii = 0; ii < buffer_height( buffer ); ++ii ) {
            m_bitset[buffer_y( buffer ) + ii] &= mask;
        }
    }

    constexpr uint32 bitset_find_free( const int width, const int height, uint32& x, uint32& y ) const noexcept {
        for ( y = 0; y < ( Pages - height ); ++y ) {
            if ( m_bitset[y] == 0xffffffff ) {
                continue;
            }

            uint32 mask = ( 1u << width ) - 1u;
            while ( x <= ( 32u - width ) ) {
                bool good = true;
                for ( int ii = 0; ii < height; ++ii ) {
                    if ( m_bitset[y + ii] & mask ) {
                        good = false;
                        break;
                    }
                }

                if ( good ) {
                    return mask;
                }

                x += 1u;
                mask <<= 1u;
            }
        }

        return 0;
    }

    uint32 m_bitset[Pages];
};

} // allocator
} // gba

#endif // define GBAXX_ALLOCATOR_BITSET_TYPES_HPP
