#ifndef GBAXX_OBJECT_OAM_ALLOCATOR_HPP
#define GBAXX_OBJECT_OAM_ALLOCATOR_HPP

#if defined( __agb_abi )
#include <gba/ext/agbabi.hpp>

extern "C" {
void __aeabi_memcpy4( void * dest, const void * src, std::size_t n );
}
#else
#include <gba/bios/cpu_copy.hpp>
#endif

#include <gba/object/attributes.hpp>

namespace gba {
namespace allocator {

class oam_buffer {
public:
    constexpr oam_buffer( const uint32 shift, const uint32 bits ) noexcept : m_shift( shift ), m_bits( bits ) {}

    constexpr oam_buffer( const std::nullptr_t&& ) noexcept : m_shift( 0 ), m_bits( 0 ) {}

    constexpr operator bool() const noexcept {
        return m_bits;
    }

    constexpr bool operator==( const oam_buffer& other ) const noexcept {
        return m_shift == other.m_shift && m_bits == other.m_bits;
    }

    constexpr bool operator!=( const oam_buffer& other ) const noexcept {
        return m_shift != other.m_shift && m_bits != other.m_bits;
    }

    constexpr bool operator==( std::nullptr_t&& ) const noexcept {
        return m_bits == 0;
    }

    constexpr bool operator!=( std::nullptr_t&& ) const noexcept {
        return m_bits;
    }

    constexpr oam_buffer& operator=( std::nullptr_t&& ) noexcept {
        m_bits = 0;
        return *this;
    }

    [[nodiscard]]
    constexpr auto allocated_objects() const noexcept {
        return m_bits * 4u;
    }

    [[nodiscard]]
    constexpr auto allocated_matrices() const noexcept {
        return m_bits;
    }

    [[nodiscard]]
    constexpr auto index() const noexcept {
        return m_shift * 4u;
    }

    [[nodiscard]]
    constexpr auto affine_index() const noexcept {
        return m_shift;
    }

    [[nodiscard]]
    constexpr uint32 mask() const noexcept {
        return ( ( 1u << m_bits ) - 1u ) << m_shift;
    }

    [[nodiscard]]
    void * map() const noexcept {
        return reinterpret_cast<void *>( 0x7000000 + start() );
    }

    [[nodiscard]]
    void * map_range( const uint32 offset ) const noexcept {
        return reinterpret_cast<void *>( 0x7000000 + ( start() + offset ) );
    }

    void data( const uint32 size, const void * data ) const noexcept {
        auto * dest = reinterpret_cast<void *>( 0x7000000 + start() );
#if defined( __agb_abi )
        __aeabi_memcpy4( dest, data, size );
#else
        bios::cpu_set( data, dest, bios::transfer {
            .transfers = size / 4,
            .type = transfer::type::word
        } );
#endif
    }

    void sub_data( const uint32 offset, const uint32 size, const void * data ) const noexcept {
        auto * dest = reinterpret_cast<void *>( 0x7000000 + ( start() + offset ) );
#if defined( __agb_abi )
        __aeabi_memcpy4( dest, data, size );
#else
        bios::cpu_set( data, dest, bios::transfer {
            .transfers = size / 4,
            .type = transfer::type::word
        } );
#endif
    }

    void data2( const uint32 size, const void * data, const void * matrices ) const noexcept {
        auto * dest = reinterpret_cast<void *>( 0x7000000 + start() );
#if defined( __agb_abi )
        agbabi::oamcpy( dest, data, matrices, size );
#else
        bios::cpu_set( data, dest, bios::transfer {
            .transfers = size / 4,
            .type = transfer::type::word
        } );
        auto * matDst = reinterpret_cast<uint16 *>( dest ) + 3;
        const auto * matSrc = reinterpret_cast<const uint16 *>( matrices );
        for ( uint32 ii = 0; ii < size; ii += 8 ) {
            *matDst = *matSrc;
            matDst += 4;
            matSrc += 1;
        }
#endif
    }

    void sub_data2( const uint32 offset, const uint32 size, const void * data, const void * matrices ) const noexcept {
        auto * dest = reinterpret_cast<void *>( 0x7000000 + ( start() + offset ) );
#if defined( __agb_abi )
        agbabi::oamcpy( dest, data, matrices, size );
#else
        bios::cpu_set( data, dest, bios::transfer {
            .transfers = size / 4,
            .type = transfer::type::word
        } );
        auto * matDst = reinterpret_cast<uint16 *>( dest ) + 3;
        const auto * matSrc = reinterpret_cast<const uint16 *>( matrices );
        for ( uint32 ii = 0; ii < size; ii += 8 ) {
            *matDst = *matSrc;
            matDst += 4;
            matSrc += 1;
        }
#endif
    }

private:
    [[nodiscard]]
    constexpr uint32 start() const noexcept {
        return m_shift * 32u;
    }

    uint16 m_shift;
    uint16 m_bits;
};

class oam {
public:
    constexpr oam() noexcept : m_bitset( 0 ) {}

    [[nodiscard]]
    oam_buffer memory_protect( const void * const address, const uint32 length ) noexcept {
        const auto shift = ( reinterpret_cast<uint32>( address ) - 0x7000000 ) / 32u;
        const auto bits = ( length + 31u ) / 32u;

        const auto mask = ( ( 1u << bits ) - 1 ) << shift;
        m_bitset |= mask;
        return oam_buffer( shift, bits );
    }

    [[nodiscard]]
    constexpr oam_buffer allocate( uint32 objects ) noexcept {
        const uint32 blocks = ( objects + 3u ) / 4u;

        uint32 mask = ( ( 1u << blocks ) - 1u ) << ( 32u - blocks );
        const auto shift = alloc_blocks( blocks, mask );
        if ( shift > ( 32u - blocks ) ) {
            return nullptr;
        }

        m_bitset |= mask;
        return oam_buffer( ( 32u - shift ) - blocks, blocks );
    }

    [[nodiscard]]
    constexpr oam_buffer allocate_front( uint32 objects ) noexcept {
        const uint32 blocks = ( objects + 3u ) / 4u;

        uint32 mask = ( 1u << blocks ) - 1u;
        const auto shift = alloc_blocks_front( blocks, mask );
        if ( shift > ( 32u - blocks ) ) {
            return nullptr;
        }

        m_bitset |= mask;
        return oam_buffer( shift, blocks );
    }

    constexpr void deallocate( oam_buffer& block ) noexcept {
        m_bitset &= ~block.mask();
        block = nullptr;
    }

private:
    [[nodiscard]]
    constexpr uint32 alloc_blocks( const uint32 blocks, uint32& mask ) const noexcept {
        uint32 shift = 0;
        while ( shift <= ( 32u - blocks ) && mask & m_bitset ) {
            mask >>= 1;
            shift += 1;
        }
        return shift;
    }

    [[nodiscard]]
    constexpr uint32 alloc_blocks_front( const uint32 blocks, uint32& mask ) const noexcept {
        uint32 shift = 0;
        while ( shift <= ( 32u - blocks ) && mask & m_bitset ) {
            mask <<= 1;
            shift += 1;
        }
        return shift;
    }

    uint32 m_bitset;
};

} // allocator
} // gba

#endif // define GBAXX_OBJECT_OAM_ALLOCATOR_HPP
