#ifndef GBAXX_BIOS_HUFF_HPP
#define GBAXX_BIOS_HUFF_HPP

#include <gba/bios/swi.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace bios {

enum class huff_bit_size : uint32 {
    _4 = 4,
    _8 = 8
};

struct huff_header {
    huff_header( const huff_header& ) = default;
    huff_header( huff_header&& ) = default;

    constexpr huff_header( const huff_bit_size size, const uint32 uncompressedSize ) noexcept : size { size }, type { 2 }, uncompressed_size { uncompressedSize } {}

    huff_header& operator =( const huff_header& other ) noexcept {
        size = other.size;
        uncompressed_size = other.uncompressed_size;
        return *this;
    }

    huff_bit_size size : 4;
    const uint32 type : 4;
    uint32 uncompressed_size : 24;
};

static_assert( sizeof( huff_header ) == 4, "huff_header must be tightly packed" );

[[gnu::always_inline]]
inline void huff_un_comp( const huff_header * src, void * dst ) noexcept {
    swi<0x13, void( const void *, void * )>::call( src, dst );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_HUFF_HPP
