#ifndef GBAXX_VRAM_VRAM_BG_BLOCKS_HPP
#define GBAXX_VRAM_VRAM_BG_BLOCKS_HPP

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
    constexpr block( const uint32 mask ) noexcept : m_mask { mask } {}

    constexpr operator bool() const noexcept {
        return m_mask;
    }

    constexpr bool operator ==( const block& other ) const noexcept {
        return m_mask == other.m_mask;
    }

    constexpr bool operator !=( const block& other ) const noexcept {
        return m_mask != other.m_mask;
    }

    constexpr bool operator ==( std::nullptr_t&& ) const noexcept {
        return m_mask == 0;
    }

    constexpr bool operator !=( std::nullptr_t&& ) const noexcept {
        return m_mask;
    }

    constexpr block& operator =( std::nullptr_t&& ) noexcept {
        m_mask = 0;
        return *this;
    }

    constexpr auto operator ~() const noexcept {
        return ~m_mask;
    }
protected:
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
public:
    constexpr tile_block_4bpp( const uint32 mask, const uint32 tiles, const uint32 start ) noexcept : tile_block( mask, tiles, start )  {}
    constexpr tile_block_4bpp( std::nullptr_t&& ) noexcept : tile_block( 0, 0, 0 ) {}

    constexpr uint32 start_index() const noexcept {
        return ( m_start - ( base_block() * 0x4000u ) ) / 32u;
    }

    constexpr gba::color_depth color_depth() const noexcept {
        return gba::color_depth::bpp_4;
    }
};

class tile_block_8bpp : public tile_block {
public:
    constexpr tile_block_8bpp( const uint32 mask, const uint32 tiles, const uint32 start ) noexcept : tile_block( mask, tiles, start )  {}
    constexpr tile_block_8bpp( std::nullptr_t&& ) noexcept : tile_block( 0, 0, 0 ) {}

    constexpr uint32 start_index() const noexcept {
        return ( m_start - ( base_block() * 0x4000u ) ) / 64u;
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

} // vram
} // gba

#endif // define GBAXX_VRAM_VRAM_BG_BLOCKS_HPP
