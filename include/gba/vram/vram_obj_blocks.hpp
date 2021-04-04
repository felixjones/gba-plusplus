#ifndef GBAXX_VRAM_VRAM_OBJ_BLOCKS_HPP
#define GBAXX_VRAM_VRAM_OBJ_BLOCKS_HPP

#if defined( __agb_abi )
extern "C" {
void __aeabi_memcpy4( void * dest, const void * src, size_t n );
}
#else
#include <gba/bios/cpu_copy.hpp>
#endif

#include <gba/types/int_type.hpp>

namespace gba {
namespace vram {

class obj_block {
public:
    constexpr obj_block( const uint32 x, const uint32 y, const uint32 width, const uint32 height ) noexcept : x( x ), y( y ), width( width ), height( height ) {}
    constexpr obj_block( std::nullptr_t&& ) noexcept : x(), y(), width(), height() {}

    constexpr uint32 start() const noexcept {
        return x + ( y * 32u );
    }

protected:
    uint8 x; // shift
    uint8 y; // page
    uint8 width; // bits
    uint8 height; // Y bits
};

class obj_tile_block : public obj_block {
public:
    constexpr obj_tile_block( const uint32 address, const uint32 x, const uint32 y, const uint32 width, const uint32 height ) noexcept : obj_block( x, y, width, height ), address { address } {}
    constexpr obj_tile_block( std::nullptr_t&& ) noexcept : obj_block( nullptr ), address() {}

    void data( const uint32 size, const void * data ) const noexcept {
        auto * dest = reinterpret_cast<void *>( address );
#if defined( __agb_abi )
        __aeabi_memcpy4( dest, data, size );
#else
        bios::cpu_fast_set( data, dest, bios::fast_transfer {
            .transfers = size / 4
        } );
#endif
    }

    void sub_data( const uint32 offset, const uint32 size, const void * data ) const noexcept {
        auto * dest = reinterpret_cast<void *>( address + offset );
#if defined( __agb_abi )
        __aeabi_memcpy4( dest, data, size );
#else
        bios::cpu_fast_set( data, dest, bios::fast_transfer {
            .transfers = size / 4
        } );
#endif
    }
private:
    uint32 address;
};

} // vram
} // gba

#endif // define GBAXX_VRAM_VRAM_OBJ_BLOCKS_HPP
