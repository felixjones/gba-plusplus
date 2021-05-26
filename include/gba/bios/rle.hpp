#ifndef GBAXX_BIOS_RLE_HPP
#define GBAXX_BIOS_RLE_HPP

#include <gba/bios/swi.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace bios {

struct rle_header {
    rle_header( const rle_header& ) = default;
    rle_header( rle_header&& ) = default;

    constexpr rle_header( const uint32 uncompressedSize ) noexcept : type { 3 }, uncompressed_size { uncompressedSize } {}

    rle_header& operator =( const rle_header& other ) noexcept {
        uncompressed_size = other.uncompressed_size;
        return *this;
    }

    uint32 : 4;
    const uint32 type : 4;
    uint32 uncompressed_size : 24;
};

static_assert( sizeof( rle_header ) == 4, "rle_header must be tightly packed" );

[[gnu::always_inline]]
inline void rle_un_comp_write_8bit( const rle_header * src, void * dst ) noexcept {
    swi<0x14, void( const void *, void * )>::call( src, dst );
}

[[gnu::always_inline]]
inline void rle_un_comp_write_16bit( const rle_header * src, void * dst ) noexcept {
    swi<0x15, void( const void *, void * )>::call( src, dst );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_RLE_HPP
