#ifndef GBAXX_ALLOCATOR_PALETTE_HPP
#define GBAXX_ALLOCATOR_PALETTE_HPP

#include <gba/registers/dma.hpp>
#include <gba/types/int_type.hpp>

#if defined( __agb_abi )
#include <cstddef>

extern "C" {
void __aeabi_memcpy( void * dest, const void * src, std::size_t n );
}
#else
#include <gba/bios/cpu_copy.hpp>
#endif

namespace gba {
namespace allocator {

class palette_buffer {
public:
    constexpr palette_buffer( const uint32 shift, const uint32 bits ) noexcept : m_shift( shift ), m_bits( bits ) {}

    constexpr palette_buffer( const std::nullptr_t&& ) noexcept : m_shift( 0 ), m_bits( 0 ) {}

    constexpr operator bool() const noexcept {
        return m_bits;
    }

    constexpr bool operator==( const palette_buffer& other ) const noexcept {
        return m_shift == other.m_shift && m_bits == other.m_bits;
    }

    constexpr bool operator!=( const palette_buffer& other ) const noexcept {
        return m_shift != other.m_shift && m_bits != other.m_bits;
    }

    constexpr bool operator==( std::nullptr_t&& ) const noexcept {
        return m_bits == 0;
    }

    constexpr bool operator!=( std::nullptr_t&& ) const noexcept {
        return m_bits;
    }

    constexpr palette_buffer& operator=( std::nullptr_t&& ) noexcept {
        m_bits = 0;
        return *this;
    }

    [[nodiscard]]
    constexpr uint32 mask() const noexcept {
        return ( ( 1u << m_bits ) - 1u ) << m_shift;
    }

    [[nodiscard]]
    void * map() const noexcept {
        return reinterpret_cast<void *>( 0x5000000 + start() );
    }

    [[nodiscard]]
    void * map_range( const uint32 offset ) const noexcept {
        return reinterpret_cast<void *>( 0x5000000 + ( start() + offset ) );
    }

    void data( const uint32 size, const void * data ) const noexcept {
        auto * dest = reinterpret_cast<void *>( 0x5000000 + start() );
#if defined( __agb_abi )
        __aeabi_memcpy4( dest, data, size );
#else
        bios::cpu_set( data, dest, bios::transfer {
            .transfers = size / 2,
            .type = bios::transfer::type::half
        } );
#endif
    }

    void sub_data( const uint32 offset, const uint32 size, const void * data ) const noexcept {
        auto * dest = reinterpret_cast<void *>( 0x5000000 + ( start() + offset ) );
#if defined( __agb_abi )
        __aeabi_memcpy4( dest, data, size );
#else
        bios::cpu_set( data, dest, bios::transfer {
            .transfers = size / 2,
            .type = bios::transfer::type::half
        } );
#endif
    }

    void dma3_data( const uint32 size, const void * data ) const noexcept {
        auto * dest = reinterpret_cast<void *>( 0x5000000 + start() );

        reg::dma3cnt_h::write( {} );
        reg::dma3sad::write( reinterpret_cast<uint32>( data ) );
        reg::dma3dad::write( reinterpret_cast<uint32>( dest ) );
        reg::dma3cnt::write( {
            .transfers = uint16( size / 2 ),
            .control = { .enable = true }
        } );
    }

    void dma3_sub_data( const uint32 offset, const uint32 size, const void * data ) const noexcept {
        auto * dest = reinterpret_cast<void *>( 0x5000000 + ( start() + offset ) );

        reg::dma3cnt_h::write( {} );
        reg::dma3sad::write( reinterpret_cast<uint32>( data ) );
        reg::dma3dad::write( reinterpret_cast<uint32>( dest ) );
        reg::dma3cnt::write( {
            .transfers = uint16( size / 2 ),
            .control = { .enable = true }
        } );
    }

private:
    [[nodiscard]]
    constexpr uint32 start() const noexcept {
        return m_shift * 32u;
    }

    uint16 m_shift;
    uint16 m_bits;
};

class palette {
public:
    constexpr palette() noexcept : m_bitset( 0 ) {}

    [[nodiscard]]
    palette_buffer memory_protect( const void * const address, const uint32 length ) noexcept {
        const auto shift = ( reinterpret_cast<uint32>( address ) - 0x5000000 ) / 32u;
        const auto bits = ( length + 31u ) / 32u;

        const auto mask = ( ( 1u << bits ) - 1 ) << shift;
        m_bitset |= mask;
        return palette_buffer( shift, bits );
    }

    [[nodiscard]]
    constexpr palette_buffer allocate_background( uint32 colors ) noexcept {
        const uint32 blocks = ( colors + 15u ) / 16u;

        uint32 mask = ( ( 1u << blocks ) - 1u ) << ( 16u - blocks );
        const auto shift = alloc_background_blocks( blocks, mask );
        if ( shift > ( 16u - blocks ) ) {
            return nullptr;
        }

        m_bitset |= mask;
        return palette_buffer( ( 16u - shift ) - blocks, blocks );
    }

    [[nodiscard]]
    constexpr palette_buffer allocate_object( uint32 colors ) noexcept {
        const uint32 blocks = ( colors + 15u ) / 16u;

        uint32 mask = ( ( 1u << blocks ) - 1u ) << ( 16u - blocks + 16u );
        const auto shift = alloc_object_blocks( blocks, mask );
        if ( shift > ( 32u - blocks ) ) {
            return nullptr;
        }

        m_bitset |= mask;
        return palette_buffer( ( 32u - shift ) - blocks + 16u, blocks );
    }

private:
    [[nodiscard]]
    constexpr uint32 alloc_background_blocks( const uint32 blocks, uint32& mask ) const noexcept {
        uint32 shift = 0;
        while ( shift <= ( 16u - blocks ) && mask & m_bitset ) {
            mask >>= 1;
            shift += 1;
        }
        return shift;
    }

    [[nodiscard]]
    constexpr uint32 alloc_object_blocks( const uint32 blocks, uint32& mask ) const noexcept {
        uint32 shift = 16u;
        while ( shift <= ( 32u - blocks ) && mask & m_bitset ) {
            mask >>= 1;
            shift += 1;
        }
        return shift;
    }

    uint32 m_bitset;
};

} // allocator
} // gba

#endif // define GBAXX_ALLOCATOR_PALETTE_HPP
