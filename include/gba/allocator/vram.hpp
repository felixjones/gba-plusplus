#ifndef GBAXX_ALLOCATOR_VRAM_HPP
#define GBAXX_ALLOCATOR_VRAM_HPP

namespace gba {
namespace allocator {

template <unsigned Mode>
struct mode {};

class buffer {
public:
    constexpr buffer( const uint32 address, const uint32 x, const uint32 y, const uint32 width, const uint32 height ) noexcept : m_address( address ), m_x( x ), m_y( y ), m_width( width ), m_height( height ) {}
    constexpr buffer( std::nullptr_t&& ) noexcept : m_address(), m_x(), m_y(), m_width(), m_height() {}

    constexpr operator bool() const noexcept {
        return m_address;
    }

    constexpr bool operator ==( std::nullptr_t&& ) const noexcept {
        return !m_address;
    }

    constexpr bool operator !=( std::nullptr_t&& ) const noexcept {
        return m_address;
    }

protected:
    friend class simple_bitset;

    uint32 m_address;
    uint8 m_x;
    uint8 m_y;
    uint8 m_width;
    uint8 m_height;
};

class simple_bitset {
protected:
    constexpr void unset( buffer& buffer ) noexcept {
        m_bitset &= ~( ( ( 1u << buffer.m_width ) - 1u ) << buffer.m_x );
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

} // allocator
} // gba

#include <gba/allocator/mode0.hpp>
#include <gba/allocator/mode1.hpp>
#include <gba/allocator/mode2.hpp>

#endif // define GBAXX_ALLOCATOR_VRAM_HPP
