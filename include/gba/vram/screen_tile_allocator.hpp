#ifndef GBAXX_VRAM_SCREEN_TILE_ALLOCATOR_HPP
#define GBAXX_VRAM_SCREEN_TILE_ALLOCATOR_HPP

#if defined( __agb_abi )
extern "C" {
void __aeabi_memcpy4( void * dest, const void * src, size_t n );
}
#else
#include <gba/bios/cpu_copy.hpp>
#endif

#include <gba/display/background_control.hpp>
#include <gba/io/background_mode.hpp>
#include <gba/types/int_type.hpp>
#include <gba/vram/screen_tile.hpp>

namespace gba {
namespace vram {

    class block {
    public:
        constexpr operator bool() const noexcept {
            return m_mask;
        }

        constexpr bool operator ==( const block& other ) const noexcept {
            return m_mask == other.m_mask;
        }

        constexpr bool operator !=( const block& other ) const noexcept {
            return m_mask == other.m_mask;
        }

        constexpr bool operator ==( std::nullptr_t&& ) const noexcept {
            return m_mask;
        }

        constexpr bool operator !=( std::nullptr_t&& ) const noexcept {
            return m_mask;
        }

        constexpr block& operator =( std::nullptr_t&& ) noexcept {
            m_mask = 0;
            return *this;
        }

        constexpr block( const uint32 mask ) noexcept : m_mask { mask } {}

    protected:
        friend class allocator;

        uint32 m_mask;
    };

    class tile_block : public block {
    public:
        [[nodiscard]]
        constexpr auto allocated_tiles() const noexcept {
            return m_tiles;
        }

        constexpr uint32 base_block() const noexcept {
            return m_start / 0x4000u;
        }

        [[nodiscard]]
        void * map() const noexcept {
            return reinterpret_cast<void *>( 0x6000000 + m_start );
        }

        [[nodiscard]]
        void * map_range( const uint32 offset ) const noexcept {
            return reinterpret_cast<void *>( 0x6000000 + ( m_start + offset ) );
        }

        void data( const uint32 size, const void * data ) const noexcept {
            auto * dest = reinterpret_cast<void *>( 0x6000000 + m_start );
#if defined( __agb_abi )
            __aeabi_memcpy4( dest, data, size );
#else
            bios::cpu_fast_set( data, dest, bios::fast_transfer {
                .transfers = size / 4
            } );
#endif
        }

        void sub_data( const uint32 offset, const uint32 size, const void * data ) const noexcept {
            auto * dest = reinterpret_cast<void *>( 0x6000000 + ( m_start + offset ) );
#if defined( __agb_abi )
            __aeabi_memcpy4( dest, data, size );
#else
            bios::cpu_fast_set( data, dest, bios::fast_transfer {
                .transfers = size / 4
            } );
#endif
        }
    protected:
        constexpr tile_block( const uint32 mask, const uint32 tiles, const uint32 start ) noexcept : block( mask ), m_tiles( tiles ), m_start( start ) {}

        const uint16 m_tiles;
        const uint16 m_start;
    };

    class tile_block_4bpp : public tile_block {
    private:
        static constexpr auto tile_size = 32u;
    public:

        [[nodiscard]]
        static constexpr uint32 round_up( const uint32 count ) noexcept {
            return ( count + 63u ) & ~63u;
        }

        constexpr tile_block_4bpp( const uint32 mask, const uint32 tiles, const uint32 start ) noexcept : tile_block( mask, tiles, start )  {}
        constexpr tile_block_4bpp( std::nullptr_t&& ) noexcept : tile_block( 0, 0, 0 ) {}

        constexpr uint32 start_index() const noexcept {
            return ( m_start - ( base_block() * 0x4000u ) ) / tile_size;
        }

        constexpr gba::color_depth color_depth() const noexcept {
            return gba::color_depth::bpp_4;
        }
    };

    class tile_block_8bpp : public tile_block {
    private:
        static constexpr auto tile_size = 64u;
    public:
        [[nodiscard]]
        static constexpr uint32 round_up( const uint32 count ) noexcept {
            return ( count + 31u ) & ~31u;
        }

        constexpr tile_block_8bpp( const uint32 mask, const uint32 tiles, const uint32 start ) noexcept : tile_block( mask, tiles, start )  {}
        constexpr tile_block_8bpp( std::nullptr_t&& ) noexcept : tile_block( 0, 0, 0 ) {}

        constexpr uint32 start_index() const noexcept {
            return ( m_start - ( base_block() * 0x4000u ) ) / tile_size;
        }

        constexpr gba::color_depth color_depth() const noexcept {
            return gba::color_depth::bpp_8;
        }
    };

    class screen_block : public block {
    public:
        [[nodiscard]]
        constexpr uint32 base_block() const noexcept {
            return m_start / 0x800u;
        }

        void data( const uint32 size, const void * data ) const noexcept {
            auto * dest = reinterpret_cast<void *>( 0x6000000 + m_start );
#if defined( __agb_abi )
            __aeabi_memcpy4( dest, data, size );
#else
            bios::cpu_fast_set( data, dest, bios::fast_transfer {
                .transfers = size / 4
            } );
#endif
        }

        void sub_data( const uint32 offset, const uint32 size, const void * data ) const noexcept {
            auto * dest = reinterpret_cast<void *>( 0x6000000 + ( m_start + offset ) );
#if defined( __agb_abi )
            __aeabi_memcpy4( dest, data, size );
#else
            bios::cpu_fast_set( data, dest, bios::fast_transfer {
                .transfers = size / 4
            } );
#endif
        }

    protected:
        constexpr screen_block( const uint32 mask, const uint32 start ) noexcept : block( mask ), m_start( start ) {}

        const uint32 m_start;
    };

    class screen_block_regular : public screen_block {
    public:
        constexpr screen_block_regular( const uint32 mask, const io::regular_screen_size size, const uint32 start ) noexcept : screen_block( mask, start ), m_size { size } {}
        constexpr screen_block_regular( std::nullptr_t&& ) noexcept : screen_block( 0, 0 ), m_size {} {}

        [[nodiscard]]
        regular_tile * map() const noexcept {
            return reinterpret_cast<regular_tile *>( 0x6000000 + m_start );
        }

        [[nodiscard]]
        regular_tile * map_range( const uint32 offset ) const noexcept {
            return reinterpret_cast<regular_tile *>( 0x6000000 + ( m_start + offset ) );
        }

        constexpr auto size() const noexcept {
            return m_size;
        }

    private:
        const io::regular_screen_size m_size;
    };

    class screen_block_affine : public screen_block {
    public:
        constexpr screen_block_affine( const uint32 mask, const io::affine_screen_size size, const uint32 start ) noexcept : screen_block( mask, start ), m_size { size } {}
        constexpr screen_block_affine( std::nullptr_t&& ) noexcept : screen_block( 0, 0 ), m_size {} {}

        [[nodiscard]]
        uint8 * map() const noexcept {
            return reinterpret_cast<uint8 *>( 0x6000000 + m_start );
        }

        [[nodiscard]]
        uint8 * map_range( const uint32 offset ) const noexcept {
            return reinterpret_cast<uint8 *>( 0x6000000 + ( m_start + offset ) );
        }

        constexpr auto size() const noexcept {
            return m_size;
        }

    private:
        const io::affine_screen_size m_size;
    };

    class allocator {
    public:
        constexpr allocator() noexcept : m_bitset { 0 } {}

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
            tiles = tile_block_4bpp::round_up( tiles );
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
            tiles = tile_block_8bpp::round_up( tiles );
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
            m_bitset &= ~block.m_mask;
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

#endif // define GBAXX_VRAM_SCREEN_TILE_ALLOCATOR_HPP
