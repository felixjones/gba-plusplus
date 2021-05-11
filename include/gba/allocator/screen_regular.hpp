#ifndef GBAXX_ALLOCATOR_SCREEN_REGULAR_HPP
#define GBAXX_ALLOCATOR_SCREEN_REGULAR_HPP

#include <algorithm>

#include <gba/allocator/buffer.hpp>
#include <gba/registers/dma.hpp>
#include <gba/types/screen_size.hpp>
#include <gba/types/screen_tile.hpp>

#if defined( __agb_abi )
#include <cstddef>

extern "C" {
void __aeabi_memcpy( void * dest, const void * src, std::size_t n );
}
#else
#include <gba/bios/cpu_copy.hpp>
#endif

namespace gba {

class buffer_screen_regular : public allocator::buffer {
public:
    constexpr buffer_screen_regular( const uint32 address, const uint32 baseBlock, const screen_size_regular screenSize, const uint32 x, const uint32 width ) noexcept : allocator::buffer( address, x, 0, width, 1 ), m_baseBlock( baseBlock ), m_screenSize( screenSize ){}
    constexpr buffer_screen_regular( std::nullptr_t&& ) noexcept : allocator::buffer( nullptr ), m_baseBlock(), m_screenSize() {}

    [[nodiscard]]
    screen_tile * map() noexcept {
        return reinterpret_cast<screen_tile *>( m_address );
    }

    [[nodiscard]]
    screen_tile * map_range( const uint32 offset ) noexcept {
        return reinterpret_cast<screen_tile *>( m_address + offset );
    }

    [[nodiscard]]
    constexpr uint32 size() const noexcept {
        return screen_count( m_screenSize ) * 0x800;
    }

    uint32 data( uint32 size, const void * data ) noexcept {
        size = std::min( size, this->size() );

        auto * dest = map();
#if defined( __agb_abi )
        __aeabi_memcpy( dest, data, size );
#else
        bios::cpu_set( data, dest, bios::transfer {
            .transfers = size / 2,
            .type = bios::transfer::type::half
        } );
#endif
        return size;
    }

    uint32 sub_data( const uint32 offset, uint32 size, const void * data ) noexcept {
        size = std::min( size, this->size() - offset );

        auto * dest = map_range( offset );
#if defined( __agb_abi )
        __aeabi_memcpy( dest, data, size );
#else
        bios::cpu_set( data, dest, bios::transfer {
            .transfers = size / 2,
            .type = bios::transfer::type::half
        } );
#endif
        return size;
    }

    uint32 dma3_data( uint32 size, const void * data ) noexcept {
        size = std::min( size, this->size() );
        auto * dest = map();

        reg::dma3cnt_h::write( {} );
        reg::dma3sad::write( reinterpret_cast<uint32>( data ) );
        reg::dma3dad::write( reinterpret_cast<uint32>( dest ) );
        reg::dma3cnt::write( {
            .transfers = uint16( size / 2 ),
            .control = { .enable = true }
        } );
        return size;
    }

    uint32 dma3_sub_data( const uint32 offset, uint32 size, const void * data ) noexcept {
        size = std::min( size, this->size() - offset );
        auto * dest = map_range( offset );

        reg::dma3cnt_h::write( {} );
        reg::dma3sad::write( reinterpret_cast<uint32>( data ) );
        reg::dma3dad::write( reinterpret_cast<uint32>( dest ) );
        reg::dma3cnt::write( {
            .transfers = uint16( size / 2 ),
            .control = { .enable = true }
        } );
        return size;
    }

    [[nodiscard]]
    constexpr uint32 base_block() const noexcept {
        return m_baseBlock;
    }

    [[nodiscard]]
    constexpr screen_size_regular screen_size() const noexcept {
        return m_screenSize;
    }

protected:
    uint32 m_baseBlock : 5;
    screen_size_regular m_screenSize : 2;
};

} // gba

#endif // define GBAXX_ALLOCATOR_SCREEN_REGULAR_HPP
