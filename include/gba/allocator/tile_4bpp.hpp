#ifndef GBAXX_ALLOCATOR_TILE_4BPP_HPP
#define GBAXX_ALLOCATOR_TILE_4BPP_HPP

#include <algorithm>

#include <gba/allocator/buffer.hpp>
#include <gba/types/color.hpp>

#if defined( __agb_abi )
#include <cstddef>

extern "C" {
void __aeabi_memcpy4( void * dest, const void * src, std::size_t n );
}
#else
#include <gba/bios/cpu_copy.hpp>
#endif

namespace gba {

class buffer_tile4bpp : public allocator::buffer {
public:
    constexpr buffer_tile4bpp( const uint32 address, const uint32 tiles, const uint32 startIndex, const uint32 baseBlock, const uint32 x, const uint32 width ) noexcept : allocator::buffer( address, x, 0, width, 1 ), m_tiles( tiles ), m_startIndex( startIndex ), m_baseBlock( baseBlock ) {}
    constexpr buffer_tile4bpp( const uint32 address, const uint32 tiles, const uint32 startIndex, const uint32 baseBlock, const uint32 x, const uint32 y, const uint32 width, const uint32 height ) noexcept : allocator::buffer( address, x, y, width, height ), m_tiles( tiles ), m_startIndex( startIndex ), m_baseBlock( baseBlock ) {}
    constexpr buffer_tile4bpp( std::nullptr_t&& ) noexcept : allocator::buffer( nullptr ), m_tiles(), m_startIndex(), m_baseBlock() {}

    [[nodiscard]]
    void * map() noexcept {
        return reinterpret_cast<void *>( m_address );
    }

    [[nodiscard]]
    void * map_range( const uint32 offset ) noexcept {
        return reinterpret_cast<void *>( m_address + offset );
    }

    [[nodiscard]]
    constexpr uint32 size() const noexcept {
        return m_tiles * 0x20;
    }

    uint32 data( uint32 size, const void * data ) noexcept {
        size = std::min( size, this->size() );

        auto * dest = map();
#if defined( __agb_abi )
        __aeabi_memcpy4( dest, data, size );
#else
        bios::cpu_fast_set( data, dest, bios::fast_transfer {
            .transfers = size / 4
        } );
#endif
        return size;
    }

    uint32 sub_data( const uint32 offset, uint32 size, const void * data ) noexcept {
        size = std::min( size, this->size() - offset );

        auto * dest = map_range( offset );
#if defined( __agb_abi )
        __aeabi_memcpy4( dest, data, size );
#else
        bios::cpu_fast_set( data, dest, bios::fast_transfer {
            .transfers = size / 4
        } );
#endif
        return size;
    }

    [[nodiscard]]
    constexpr uint32 start_index() const noexcept {
        return m_startIndex;
    }

    [[nodiscard]]
    constexpr uint32 base_block() const noexcept {
        return m_baseBlock;
    }

    [[nodiscard]]
    constexpr gba::color_depth color_depth() const noexcept {
        return gba::color_depth::bpp_4;
    }

private:
    uint16 m_tiles;
    uint16 m_startIndex : 9;
    uint16 m_baseBlock : 2;
};

} // gba

#endif // define GBAXX_ALLOCATOR_TILE_4BPP_HPP
