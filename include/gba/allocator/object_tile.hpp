#ifndef GBAXX_ALLOCATOR_OBJECT_TILE_HPP
#define GBAXX_ALLOCATOR_OBJECT_TILE_HPP

#include <gba/allocator/bitset_types.hpp>
#include <gba/allocator/buffer.hpp>
#include <gba/allocator/tile_4bpp.hpp>
#include <gba/allocator/tile_4bpp_2d.hpp>
#include <gba/allocator/tile_8bpp.hpp>
#include <gba/allocator/tile_8bpp_2d.hpp>
#include <gba/object/attributes.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace allocator {

template <unsigned Pages, unsigned Address, unsigned Length>
class object_tile : public bitset_2d<Pages> {
public:
    static constexpr uint32 address = Address;
    static constexpr uint32 length = Length;
    static constexpr uint32 stride = 32u;

    constexpr object_tile() noexcept : bitset_2d<Pages>() {}

    void deallocate( buffer& buffer ) noexcept {
        bitset_2d<Pages>::unset( buffer );
    }

    constexpr buffer_tile4bpp2d allocate_tile4bpp( const object::shape shape, const uint32 size ) noexcept {
        const auto width = object::tile_width( shape, size );
        const auto height = object::tile_height( shape, size );

        uint32 x {};
        uint32 y {};
        const auto mask = bitset_2d<Pages>::bitset_find_free( width, height, x, y );
        if ( !mask ) {
            return nullptr;
        }

        for ( int ii = 0; ii < height; ++ii ) {
            bitset_2d<Pages>::m_bitset[y + ii] |= mask;
        }
        return buffer_tile4bpp2d( address + ( y * 0x400 ) + ( x * 0x20 ), width * height, ( y * 0x20 ) + x, stride, x, y, width, height );
    }

    constexpr buffer_tile4bpp allocate_tile4bpp( const uint32 count ) noexcept {
        if ( count > 32u ) {
            const auto height = ( count + 31u ) / 32u;
            uint32 x {};
            uint32 y {};
            const auto mask = bitset_2d<Pages>::bitset_find_free( 32u, height, x, y );
            if ( !mask ) {
                return nullptr;
            }

            for ( uint32 ii = 0; ii < height; ++ii ) {
                bitset_2d<Pages>::m_bitset[y + ii] = 0xffffffff;
            }
            return buffer_tile4bpp( address + ( y * 0x400 ), count, y * 0x20, 0, 0, y, 32u, height );
        }

        uint32 x {};
        uint32 y {};
        const auto mask = bitset_2d<Pages>::bitset_find_free( count, 1, x, y );
        if ( !mask ) {
            return nullptr;
        }

        bitset_2d<Pages>::m_bitset[y] |= mask;
        return buffer_tile4bpp( address + ( y * 0x400 ) + ( x * 0x20 ), count, ( y * 0x20 ) + x, 0, x, count );
    }

    constexpr buffer_tile8bpp2d allocate_tile8bpp( const object::shape shape, const uint32 size ) noexcept {
        const auto width = object::tile_width( shape, size ) * 2u;
        const auto height = object::tile_height( shape, size );

        uint32 x {};
        uint32 y {};
        const auto mask = bitset_2d<Pages>::bitset_find_free( width, height, x, y );
        if ( !mask ) {
            return nullptr;
        }

        for ( int ii = 0; ii < height; ++ii ) {
            bitset_2d<Pages>::m_bitset[y + ii] |= mask;
        }
        return buffer_tile8bpp2d( address + ( y * 0x400 ) + ( x * 0x20 ), ( width * height ) / 2u, ( y * 0x20 ) + x, stride, x, y, width, height );
    }

    constexpr buffer_tile8bpp allocate_tile8bpp( const uint32 count ) noexcept {
        const auto bits = count * 2u;

        if ( bits > 32u ) {
            const auto height = ( bits + 31u ) / 32u;
            uint32 x {};
            uint32 y {};
            const auto mask = bitset_2d<Pages>::bitset_find_free( 32u, height, x, y );
            if ( !mask ) {
                return nullptr;
            }

            for ( uint32 ii = 0; ii < height; ++ii ) {
                bitset_2d<Pages>::m_bitset[y + ii] = 0xffffffff;
            }
            return buffer_tile8bpp( address + ( y * 0x400 ), count, y * 0x20, 0, 0, y, 32u, height );
        }

        uint32 x {};
        uint32 y {};
        const auto mask = bitset_2d<Pages>::bitset_find_free( bits, 1, x, y );
        if ( !mask ) {
            return nullptr;
        }

        bitset_2d<Pages>::m_bitset[y] |= mask;
        return buffer_tile8bpp( address + ( y * 0x400 ) + ( x * 0x20 ), count, ( y * 0x20 ) + x, 0, x, bits );
    }
};

} // allocator
} // gba

#endif // define GBAXX_ALLOCATOR_OBJECT_TILE_HPP
