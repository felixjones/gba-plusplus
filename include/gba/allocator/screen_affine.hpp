#ifndef GBAXX_ALLOCATOR_SCREEN_AFFINE_HPP
#define GBAXX_ALLOCATOR_SCREEN_AFFINE_HPP

#include <algorithm>

#include <gba/allocator/buffer.hpp>
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

class buffer_screen_affine : public allocator::buffer {
public:
    struct tile {
        uint8 lo;
        uint8 hi;
    };

    constexpr buffer_screen_affine( const uint32 address, const uint32 baseBlock, const screen_size_affine screenSize, const uint32 x, const uint32 width ) noexcept : allocator::buffer( address, x, 0, width, 1 ), m_baseBlock( baseBlock ), m_screenSize( screenSize ){}
    constexpr buffer_screen_affine( std::nullptr_t&& ) noexcept : allocator::buffer( nullptr ), m_baseBlock(), m_screenSize() {}

    [[nodiscard]]
    tile * map() noexcept {
        return reinterpret_cast<tile *>( m_address );
    }

    [[nodiscard]]
    tile * map_range( const uint32 offset ) noexcept {
        return reinterpret_cast<tile *>( m_address + offset );
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
        size = std::min( size, this->size() - offset ) & 0xfffffffe;

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

    [[nodiscard]]
    constexpr uint32 base_block() const noexcept {
        return m_baseBlock;
    }

    [[nodiscard]]
    constexpr screen_size_affine screen_size() const noexcept {
        return m_screenSize;
    }

protected:
    uint32 m_baseBlock : 5;
    screen_size_affine m_screenSize : 2;
};

} // gba

#endif // define GBAXX_ALLOCATOR_SCREEN_AFFINE_HPP
