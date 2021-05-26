#ifndef GBAXX_BIOS_COMPRESSION_HPP
#define GBAXX_BIOS_COMPRESSION_HPP

#include <gba/bios/swi.hpp>
#include <gba/types/int_type.hpp>

namespace gba {
namespace bios {

enum class un_pack_bits : uint8 {
    _1 = 1,
    _2 = 2,
    _4 = 4,
    _8 = 8,
};

struct bit_un_pack_input {
    uint16 size;
    un_pack_bits source_width;
    un_pack_bits destination_width;
    uint32 data_offset : 31;
    bool zero_data : 1;
};

static_assert( sizeof( bit_un_pack_input ) == 8, "bit_un_pack_input must be tightly packed" );

[[gnu::always_inline]]
inline void bit_un_pack( const void * src, void * dst, const bit_un_pack_input * input ) noexcept {
    swi<0x10, void( const void *, void *, const void * )>::call( src, dst, input );
}

enum class un_filter_size : uint32 {
    bit_8 = 1,
    bit_16 = 2
};

struct diff_un_filter_header {
    diff_un_filter_header( const diff_un_filter_header& ) = default;
    diff_un_filter_header( diff_un_filter_header&& ) = default;

    constexpr diff_un_filter_header( const un_filter_size size, const uint32 uncompressedSize ) noexcept : size { size }, type { 8 }, uncompressed_size { uncompressedSize } {}

    diff_un_filter_header& operator =( const diff_un_filter_header& other ) noexcept {
        size = other.size;
        uncompressed_size = other.uncompressed_size;
        return *this;
    }

    un_filter_size size : 4;
    const uint32 type : 4;
    uint32 uncompressed_size : 24;
};

static_assert( sizeof( diff_un_filter_header ) == 4, "diff_un_filter_header must be tightly packed" );

[[gnu::always_inline]]
inline void diff_8bit_un_filter_write_8bit( const diff_un_filter_header * src, void * dst ) noexcept {
    swi<0x16, void( const void *, void * )>::call( src, dst );
}

[[gnu::always_inline]]
inline void diff_8bit_un_filter_write_16bit( const diff_un_filter_header * src, void * dst ) noexcept {
    swi<0x17, void( const void *, void * )>::call( src, dst );
}

[[gnu::always_inline]]
inline void diff_16bit_un_filter( const diff_un_filter_header * src, void * dst ) noexcept {
    swi<0x18, void( const void *, void * )>::call( src, dst );
}

} // bios
} // gba

#endif // define GBAXX_BIOS_COMPRESSION_HPP
