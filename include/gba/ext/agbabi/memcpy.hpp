#ifndef GBAXX_EXT_AGBABI_MEMCPY_HPP
#define GBAXX_EXT_AGBABI_MEMCPY_HPP

#if defined( __agb_abi )

#include <cstddef>

extern "C" {

void __agbabi_rmemcpy4( void * dest, const void * src, std::size_t n );
void __agbabi_rmemcpy( void * dest, const void * src, std::size_t n );
void __agbabi_wordset4( void * dest, std::size_t n, int c );
void __agbabi_oamcpy( void * dest, const void * srcA, const void * srcB, std::size_t n );
void __agbabi_oamset( void * dest, const void * srcA, const void * srcB, std::size_t n );

}

namespace gba {
namespace agbabi {

void rmemcpy4( void * dest, const void * src, std::size_t n ) noexcept {
    __agbabi_rmemcpy4( dest, src, n );
}

void rmemcpy( void * dest, const void * src, std::size_t n ) noexcept {
    __agbabi_rmemcpy( dest, src, n );
}

void wordset4( void * dest, std::size_t n, int c ) noexcept {
    __agbabi_wordset4( dest, n, c );
}

void oamcpy( void * dest, const void * srcA, const void * srcB, std::size_t n ) noexcept {
    __agbabi_oamcpy( dest, srcA, srcB, n );
}

void oamset( void * dest, const void * srcA, const void * srcB, std::size_t n ) noexcept {
    __agbabi_oamset( dest, srcA, srcB, n );
}

} // agbabi
} // gba

#endif // __agb_abi

#endif // define GBAXX_EXT_AGBABI_MEMCPY_HPP
