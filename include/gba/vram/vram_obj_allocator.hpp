#ifndef GBAXX_VRAM_VRAM_OBJ_ALLOCATOR_HPP
#define GBAXX_VRAM_VRAM_OBJ_ALLOCATOR_HPP

#include <gba/types/int_type.hpp>
#include <gba/vram/vram_obj_blocks.hpp>

namespace gba {
namespace vram {

template <unsigned Size, unsigned Address>
class obj_allocator {
public:
    constexpr obj_allocator() noexcept {}

    [[nodiscard]]
    constexpr obj_tile_block allocate_tile8bpp( const uint32 tiles ) noexcept {
        if ( tiles >= 16u ) [[unlikely]] {
            const auto height = ( tiles + 15u ) / 16u;
            const auto y = alloc_pages( height );
            if ( y == 0xffffffff ) {
                return nullptr;
            }

            for ( uint32 ii = 0; ii < height; ++ii ) {
                m_bitset[y + ii] = 0xffffffff;
            }
            return obj_tile_block( Address + ( y * 32u ) * 32u, 0, y, 32, height );
        }

        const auto width = tiles * 2u;
        uint32 x = 0, y = 0;
        const auto mask = alloc_blocks2( width, x, y );
        if ( !mask ) {
            return nullptr;
        }

        m_bitset[y] |= mask;
        return obj_tile_block( Address + ( x + ( y * 32u ) ) * 32u, x, y, width, 1 );
    }

    [[nodiscard]]
    constexpr obj_tile_block allocate_tile4bpp( uint32 tiles ) noexcept {
        if ( tiles >= 32u ) [[unlikely]] {
            const auto height = ( tiles + 31u ) / 32u;
            const auto y = alloc_pages( height );
            if ( y == 0xffffffff ) {
                return nullptr;
            }

            for ( uint32 ii = 0; ii < height; ++ii ) {
                m_bitset[y + ii] = 0xffffffff;
            }
            return obj_tile_block( Address + ( y * 32u ) * 32u, 0, y, 32, height );
        }

        const auto width = tiles;
        uint32 x = 0, y = 0;
        const auto mask = alloc_blocks( width, x, y );
        if ( !mask ) {
            return nullptr;
        }

        m_bitset[y] |= mask;
        return obj_tile_block( Address + ( x + ( y * 32u ) ) * 32u, x, y, width, 1 );
    }
private:
    [[nodiscard]]
    constexpr uint32 alloc_pages( const uint32 pages ) const noexcept {
        for ( uint32 ii = 0; ii < Size; ++ii ) {
            uint32 jj = 0;
            while ( m_bitset[ii + jj] == 0 && jj < pages ) {
                ++jj;
            }

            if ( jj == pages ) {
                return ii;
            }
        }
        return -1;
    }

    [[nodiscard]]
    constexpr uint32 alloc_blocks2( const uint32 bits, uint32& outShift, uint32& outPage ) const noexcept {
        for ( uint32 ii = 0; ii < Size; ++ii ) {
            auto mask = ( 1u << bits ) - 1u;
            for ( uint32 jj = 0; jj < 32u - bits; jj += 2 ) {
                if ( ( mask & m_bitset[ii] ) == 0 ) {
                    outShift = jj;
                    outPage = ii;
                    return mask;
                }
                mask <<= 2u;
            }
        }
        return 0u;
    }

    [[nodiscard]]
    constexpr uint32 alloc_blocks( const uint32 bits, uint32& outShift, uint32& outPage ) const noexcept {
        for ( uint32 ii = 0; ii < Size; ++ii ) {
            auto mask = ( 1u << bits ) - 1u;
            for ( uint32 jj = 0; jj < 32u - bits; ++jj ) {
                if ( ( mask & m_bitset[ii] ) == 0 ) {
                    outShift = jj;
                    outPage = ii;
                    return mask;
                }
                mask <<= 1u;
            }
        }
        return 0u;
    }

    uint32 m_bitset[Size];
};

} // vram
} // gba

#endif // define GBAXX_VRAM_VRAM_OBJ_ALLOCATOR_HPP
