#ifndef GBAXX_ALLOCATOR_TILE_4BPP_2D_HPP
#define GBAXX_ALLOCATOR_TILE_4BPP_2D_HPP

#include <algorithm>

#include <gba/allocator/buffer.hpp>
#include <gba/registers/dma.hpp>
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

class buffer_tile4bpp2d : public allocator::buffer {
public:
    constexpr buffer_tile4bpp2d( const uint32 address, const uint32 tiles, const uint32 startIndex, const uint32 stride, const uint32 x, const uint32 y, const uint32 width, const uint32 height ) noexcept : allocator::buffer( address, x, y, width, height ), m_tiles( tiles ), m_startIndex( startIndex ), m_stride( stride ) {}
    constexpr buffer_tile4bpp2d( std::nullptr_t&& ) noexcept : allocator::buffer( nullptr ), m_tiles(), m_startIndex(), m_stride() {}

    [[nodiscard]]
    void * map( const uint32 index ) noexcept {
        return reinterpret_cast<void *>( m_address + ( index * stride() ) );
    }

    [[nodiscard]]
    void * map_range( const uint32 index, const uint32 offset ) noexcept {
        return reinterpret_cast<void *>( m_address + ( index * stride() ) + offset );
    }

    [[nodiscard]]
    constexpr uint32 size() const noexcept {
        return m_tiles * 0x20;
    }

    uint32 data( const uint32 index, uint32 size, const void * data ) noexcept {
        size = std::min( size, this->size() / m_height );

        auto * dest = map( index );
#if defined( __agb_abi )
        __aeabi_memcpy4( dest, data, size );
#else
        bios::cpu_fast_set( data, dest, bios::fast_transfer {
            .transfers = size / 4
        } );
#endif
        return size;
    }

    uint32 sub_data( const uint32 index, const uint32 offset, uint32 size, const void * data ) noexcept {
        size = std::min( size, ( this->size() / m_height ) - offset );

        auto * dest = map_range( index, offset );
#if defined( __agb_abi )
        __aeabi_memcpy4( dest, data, size );
#else
        bios::cpu_fast_set( data, dest, bios::fast_transfer {
            .transfers = size / 4
        } );
#endif
        return size;
    }

    uint32 dma3_data( const uint32 index, uint32 size, const void * data ) noexcept {
        size = std::min( size, this->size() / m_height );
        auto * dest = map( index );

        reg::dma3cnt_h::write( {} );
        reg::dma3sad::write( reinterpret_cast<uint32>( data ) );
        reg::dma3dad::write( reinterpret_cast<uint32>( dest ) );
        reg::dma3cnt::write( {
            .transfers = uint16( size / 4 ),
             .control = { .type = dma_control::type::word, .enable = true }
        } );
        return size;
    }

    uint32 dma3_sub_data( const uint32 index, const uint32 offset, uint32 size, const void * data ) noexcept {
        size = std::min( size, ( this->size() / m_height ) - offset );
        auto * dest = map_range( index, offset );

        reg::dma3cnt_h::write( {} );
        reg::dma3sad::write( reinterpret_cast<uint32>( data ) );
        reg::dma3dad::write( reinterpret_cast<uint32>( dest ) );
        reg::dma3cnt::write( {
            .transfers = uint16( size / 4 ),
            .control = { .type = dma_control::type::word, .enable = true }
        } );
        return size;
    }

    [[nodiscard]]
    constexpr uint32 start_index() const noexcept {
        return m_startIndex;
    }

    [[nodiscard]]
    constexpr uint32 stride() const noexcept {
        return m_stride * 0x20;
    }

    [[nodiscard]]
    constexpr gba::color_depth color_depth() const noexcept {
        return gba::color_depth::bpp_4;
    }

private:
    uint16 m_tiles;
    uint16 m_startIndex : 10;
    uint16 m_stride : 6;
};

} // gba

#endif // define GBAXX_ALLOCATOR_TILE_4BPP_2D_HPP
