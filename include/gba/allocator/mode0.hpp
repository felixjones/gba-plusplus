#ifndef GBAXX_ALLOCATOR_MODE0_HPP
#define GBAXX_ALLOCATOR_MODE0_HPP

#include <gba/allocator/bitset_types.hpp>
#include <gba/allocator/buffer.hpp>
#include <gba/allocator/object_tile.hpp>
#include <gba/allocator/screen_regular.hpp>
#include <gba/allocator/tile_4bpp.hpp>
#include <gba/allocator/tile_8bpp.hpp>
#include <gba/allocator/vram.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace allocator {

template <>
struct mode<0> {

using object = object_tile<32, 0x6010000, 0x8000>;

class background : public simple_bitset {
public:
    static constexpr uint32 address = 0x6000000;
    static constexpr uint32 length = 0x10000;

    constexpr background() noexcept : simple_bitset() {}

    void deallocate( buffer& buffer ) noexcept {
        unset( buffer );
    }

    constexpr buffer_screen_regular allocate_screen( const screen_size_regular size ) noexcept {
        const uint32 bits = screen_count( size );

        uint32 shift = 0;
        const auto mask = bitset_find_free( bits, shift );
        if ( !mask ) {
            return nullptr;
        }

        m_bitset |= mask;
        return buffer_screen_regular( address + ( shift * 0x800 ), shift, size, shift, bits );
    }

    constexpr buffer_tile4bpp allocate_tile4bpp( uint32 count ) noexcept {
        count = ( ( count + 63u ) & ~63u );
        const uint32 bits = count / 64u;

        uint32 shift = 0;
        const auto mask = bitset_find_free_aligned<8>( bits, shift );
        if ( !mask ) {
            return nullptr;
        }

        m_bitset |= mask;
        return buffer_tile4bpp( address + ( shift * 0x800 ), count, shift * 64u, shift / 8u, shift, bits );
    }

    constexpr buffer_tile8bpp allocate_tile8bpp( uint32 count ) noexcept {
        count = ( ( count + 31u ) & ~31u );
        const uint32 bits = count / 32u;

        uint32 shift = 0;
        const auto mask = bitset_find_free_aligned<8>( bits, shift );
        if ( !mask ) {
            return nullptr;
        }

        m_bitset |= mask;
        return buffer_tile8bpp( address + ( shift * 0x800 ), count, shift * 64u, shift / 8u, shift, bits );
    }
};

};

} // allocator
} // gba

#endif // define GBAXX_ALLOCATOR_MODE0_HPP
