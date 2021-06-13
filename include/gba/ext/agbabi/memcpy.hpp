#ifndef GBAXX_EXT_AGBABI_MEMCPY_HPP
#define GBAXX_EXT_AGBABI_MEMCPY_HPP

#if defined( __agb_abi )

#include <cstddef>

extern "C" {

void __agbabi_memcpy2( void * dest, const void * src, std::size_t n );
void __agbabi_memmove2( void * dest, const void * src, std::size_t n );
void __agbabi_rmemcpy4( void * dest, const void * src, std::size_t n );
void __agbabi_rmemcpy2( void * dest, const void * src, std::size_t n );
void __agbabi_rmemcpy( void * dest, const void * src, std::size_t n );
void __agbabi_wordset4( void * dest, std::size_t n, int c );
void __agbabi_oamcpy( void * dest, const void * srcA, const void * srcB, std::size_t n );
void __agbabi_oamset( void * dest, const void * srcA, const void * srcB, std::size_t n );

}

namespace gba {
namespace agbabi {

inline void memcpy2( void * dest, const void * src, std::size_t n ) noexcept {
    __agbabi_memcpy2( dest, src, n );
}

inline void memmove2( void * dest, const void * src, std::size_t n ) noexcept {
    __agbabi_memmove2( dest, src, n );
}

inline void rmemcpy4( void * dest, const void * src, std::size_t n ) noexcept {
    __agbabi_rmemcpy4( dest, src, n );
}

inline void rmemcpy2( void * dest, const void * src, std::size_t n ) noexcept {
    __agbabi_rmemcpy2( dest, src, n );
}

inline void rmemcpy( void * dest, const void * src, std::size_t n ) noexcept {
    __agbabi_rmemcpy( dest, src, n );
}

inline void wordset4( void * dest, std::size_t n, int c ) noexcept {
    __agbabi_wordset4( dest, n, c );
}

inline void oamcpy( void * dest, const void * srcA, const void * srcB, std::size_t n ) noexcept {
    __agbabi_oamcpy( dest, srcA, srcB, n );
}

inline void oamset( void * dest, const void * srcA, const void * srcB, std::size_t n ) noexcept {
    __agbabi_oamset( dest, srcA, srcB, n );
}

} // agbabi
} // gba

#endif // __agb_abi

#endif // define GBAXX_EXT_AGBABI_MEMCPY_HPP
