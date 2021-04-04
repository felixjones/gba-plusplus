#ifndef GBAXX_VRAM_VRAM_BG_ALLOCATOR_HPP
#define GBAXX_VRAM_VRAM_BG_ALLOCATOR_HPP

#include <gba/types/int_type.hpp>
#include <gba/vram/vram_bg_blocks.hpp>

namespace gba {
namespace vram {

    class bg_allocator {
    public:
        constexpr bg_allocator() noexcept : m_bitset { 0 } {}

        [[nodiscard]]
        block memory_protect( const void * const address, const uint32 length ) noexcept {
            const auto start = ( reinterpret_cast<uint32>( address ) - 0x6000000 ) / 0x200;
            const auto count = ( length + 0x1ff ) / 0x200;

            const auto mask = ( ( 1u << count ) - 1 ) << start;
            m_bitset |= mask;
            return block( mask );
        }

        [[nodiscard]]
        constexpr tile_block_4bpp allocate_tile4bpp( uint32 tiles ) noexcept {
            tiles = ( tiles + 63u ) & ~63u;
            const auto blocks = tiles / 64u;

            uint32 shift = 0;
            const auto mask = alloc_tileblocks( blocks, ( 1u << blocks ) - 1u, shift );
            if ( !mask ) {
                return nullptr;
            }

            m_bitset |= mask;
            return tile_block_4bpp( mask, tiles, shift * 0x800 );
        }

        [[nodiscard]]
        constexpr tile_block_8bpp allocate_tile8bpp( uint32 tiles ) noexcept {
            tiles = ( tiles + 31u ) & ~31u;
            const auto blocks = tiles / 32u;

            uint32 shift = 0;
            const auto mask = alloc_tileblocks( blocks, ( 1u << blocks ) - 1u, shift );
            if ( !mask ) {
                return nullptr;
            }

            m_bitset |= mask;
            return tile_block_8bpp( mask, tiles, shift * 0x800 );
        }

        [[nodiscard]]
        constexpr screen_block_regular allocate_screen( const io::regular_screen_size size ) noexcept {
            uint32 screens = 0;
            switch ( size ) {
            case io::regular_screen_size::_32x32:
                screens = 1;
                break;
            case io::regular_screen_size::_64x32:
                screens = 2;
                break;
            case io::regular_screen_size::_32x64:
                screens = 2;
                break;
            case io::regular_screen_size::_64x64:
                screens = 3;
                break;
            }

            uint32 shift = 0;
            const auto mask = alloc_screenblocks( screens, ( 1u << screens ) - 1u, shift );
            if ( !mask ) {
                return nullptr;
            }

            m_bitset |= mask;
            return screen_block_regular( mask, size, shift * 0x800 );
        }

        [[nodiscard]]
        constexpr screen_block_affine allocate_affine_screen( const io::affine_screen_size size ) noexcept {
            uint32 screens = 0;
            switch ( size ) {
                case io::affine_screen_size::_16x16:
                    screens = 1;
                    break;
                case io::affine_screen_size::_32x32:
                    screens = 1;
                    break;
                case io::affine_screen_size::_64x64:
                    screens = 2;
                    break;
                case io::affine_screen_size::_128x128:
                    screens = 8;
                    break;
            }

            uint32 shift = 0;
            const auto mask = alloc_screenblocks( screens, ( 1u << screens ) - 1u, shift );
            if ( !mask ) {
                return nullptr;
            }

            m_bitset |= mask;
            return screen_block_affine( mask, size, shift * 0x800 );
        }

        constexpr void deallocate( block& block ) noexcept {
            m_bitset &= ~block;
            block = nullptr;
        }

    private:
        constexpr uint32 alloc_screenblocks( const uint32 blocks, uint32 mask, uint32& outShift ) const noexcept {
            const auto spareBlocks = 32u - blocks;

            for ( auto ii = 0u; ii <= spareBlocks; ++ii ) {
                if ( ( mask & m_bitset ) == 0 ) {
                    return mask;
                }
                mask <<= 1;
                outShift += 1;
            }

            return 0u;
        }

        constexpr uint32 alloc_tileblocks( const uint32 blocks, uint32 mask, uint32& outShift ) const noexcept {
            const auto screenBlocks = blocks <= 9u ? 32u : ( blocks + 7u ) & ~7u;
            const auto spareBlocks = ( screenBlocks - blocks );
            const auto nextCharBlock = ( 8u - spareBlocks ) - 1u;

            const auto charBlocks = ( 4u - ( screenBlocks / 8u ) );
            for ( auto jj = 0u; jj <= charBlocks; ++jj ) {
                for ( auto ii = 0u; ii <= spareBlocks; ++ii ) {
                    if ( ( mask & m_bitset ) == 0 ) {
                        return mask;
                    }
                    mask <<= 1;
                    outShift += 1;
                }
                mask <<= nextCharBlock;
                outShift += nextCharBlock;
            }

            return 0u;
        }

        uint32 m_bitset;
    };

} // vram
} // gba

#endif // define GBAXX_VRAM_VRAM_BG_ALLOCATOR_HPP
