#ifndef GBAXX_BIOS_LZ77_HPP
#define GBAXX_BIOS_LZ77_HPP

#include <gba/bios/swi.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace bios {

struct lz77_header {
    lz77_header( const lz77_header& ) = default;
    lz77_header( lz77_header&& ) = default;

    constexpr lz77_header( const uint32 uncompressedSize ) noexcept : type { 1 }, uncompressed_size { uncompressedSize } {}

    lz77_header& operator =( const lz77_header& other ) noexcept {
        uncompressed_size = other.uncompressed_size;
        return *this;
    }

    uint32 : 4;
    const uint32 type : 4;
    uint32 uncompressed_size : 24;
};

static_assert( sizeof( lz77_header ) == 4, "lz77_header must be tightly packed" );

[[gnu::always_inline]]
inline void lz77_un_comp_write_8bit( const lz77_header * src, void * dst ) noexcept {
    swi<0x11, void( const void *, void * )>::call( src, dst );
}

[[gnu::always_inline]]
inline void lz77_un_comp_write_16bit( const lz77_header * src, void * dst ) noexcept {
    swi<0x12, void( const void *, void * )>::call( src, dst );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_LZ77_HPP
