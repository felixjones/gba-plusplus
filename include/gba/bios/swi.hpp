#ifndef GBAXX_BIOS_SWI_HPP
#define GBAXX_BIOS_SWI_HPP

#include <tuple>

namespace gba {
namespace bios {

template <unsigned Swi, class Function>
struct swi;

template <unsigned Swi>
struct swi<Swi, void( void )> {
    [[gnu::always_inline]]
    static void call() noexcept {
        asm(
#if defined( __thumb__ )
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "swi\t%[Swi] << 16"
#endif
        :: [Swi]"i"( Swi ) : "r0", "r1", "r3"
        );
    }
};

template <unsigned Swi>
struct swi<Swi, void( int )> {
    [[gnu::always_inline]]
    static void call( int arg0 ) noexcept {
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "swi\t%[Swi] << 16"
#endif
        :: [Swi]"i"( Swi ), [r0]"r"( arg0 ) : "r0", "r1", "r3"
        );
    }

    [[gnu::always_inline]]
    static void call_2( int arg0 ) noexcept {
        asm(
#if defined( __thumb__ )
        "movs\tr2, %[r0]\n\t"
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "mov\tr2, %[r0]\n\t"
        "swi\t%[Swi] << 16"
#endif
        :: [Swi]"i"( Swi ), [r0]"r"( arg0 ) : "r0", "r1", "r2", "r3"
        );
    }
};

template <unsigned Swi>
struct swi<Swi, void( int, int )> {
    [[gnu::always_inline]]
    static void call( int arg0, int arg1 ) noexcept {
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "movs\tr1, %[r1]\n\t"
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "mov\tr1, %[r1]\n\t"
        "swi\t%[Swi] << 16"
#endif
        :: [Swi]"i"( Swi ), [r0]"r"( arg0 ), [r1]"r"( arg1 ) : "r0", "r1", "r3"
        );
    }
};

template <unsigned Swi>
struct swi<Swi, int( int, int )> {
    [[nodiscard, gnu::always_inline]]
    static auto call( int arg0, int arg1 ) noexcept {
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "movs\tr1, %[r1]\n\t"
        "swi\t%[Swi]\n\t"
        "movs\t%[out], r0"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "mov\tr1, %[r1]\n\t"
        "swi\t%[Swi] << 16\n\t"
        "mov\t%[out], r0"
#endif
        : [out]"+r"( arg0 ) : [Swi]"i"( Swi ), [r0]"r"( arg0 ), [r1]"r"( arg1 ) : "r0", "r1", "r3"
        );
        return arg0;
    }
};

template <unsigned Swi>
struct swi<Swi, unsigned int( unsigned int )> {
    [[nodiscard, gnu::always_inline]]
    static auto call( unsigned int arg0 ) noexcept {
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "swi\t%[Swi]\n\t"
        "movs\t%[r0], r0"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "swi\t%[Swi] << 16\n\t"
        "mov\t%[r0], r0"
#endif
        : [r0]"+r"( arg0 ) : [Swi]"i"( Swi ) : "r0", "r1", "r3"
        );
        return arg0;
    }
};

template <unsigned Swi>
struct swi<Swi, unsigned int( void )> {
    [[nodiscard, gnu::always_inline]]
    static auto call() noexcept {
        unsigned int result;
        asm(
#if defined( __thumb__ )
        "swi\t%[Swi]\n\t"
        "movs\t%[r0], r0"
#elif defined( __arm__ )
        "swi\t%[Swi] << 16\n\t"
        "mov\t%[r0], r0"
#endif
        : [r0]"+r"( result ) : [Swi]"i"( Swi ) : "r0", "r1", "r3"
        );
        return result;
    }
};

template <unsigned Swi>
struct swi<Swi, short( short )> {
    [[nodiscard, gnu::always_inline]]
    static auto call( short arg0 ) noexcept {
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "swi\t%[Swi]\n\t"
        "movs\t%[out], r0"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "swi\t%[Swi] << 16\n\t"
        "mov\t%[out], r0"
#endif
        : [out]"+r"( arg0 ) : [Swi]"i"( Swi ), [r0]"r"( arg0 ) : "r0", "r1", "r3"
        );
        return arg0;
    }
};

template <unsigned Swi>
struct swi<Swi, short( short, short )> {
    [[nodiscard, gnu::always_inline]]
    static auto call( short arg0, short arg1 ) noexcept {
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "movs\tr1, %[r1]\n\t"
        "swi\t%[Swi]\n\t"
        "movs\t%[out], r0"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "mov\tr1, %[r1]\n\t"
        "swi\t%[Swi] << 16\n\t"
        "mov\t%[out], r0"
#endif
        : [out]"+r"( arg0 ) : [Swi]"i"( Swi ), [r0]"r"( arg0 ), [r1]"r"( arg1 ) : "r0", "r1", "r3"
        );
        return arg0;
    }
};

template <unsigned Swi>
struct swi<Swi, std::tuple<int, int, unsigned int>( int, int )> {
    [[nodiscard, gnu::always_inline]]
    static auto call( int arg0, int arg1 ) noexcept {
        unsigned int r3;
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "movs\tr1, %[r1]\n\t"
        "swi\t%[Swi]\n\t"
        "movs\t%[r0], r0\n\t"
        "movs\t%[r1], r1\n\t"
        "movs\t%[r3], r3"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "mov\tr1, %[r1]\n\t"
        "swi\t%[Swi] << 16\n\t"
        "mov\t%[r0], r0\n\t"
        "mov\t%[r1], r1\n\t"
        "mov\t%[r3], r3"
#endif
        : [r0]"+r"( arg0 ), [r1]"+r"( arg1 ), [r3]"+r"( r3 )
        : [Swi]"i"( Swi ) : "r0", "r1", "r3"
        );
        return std::make_tuple( arg0, arg1, r3 );
    }
};

template <unsigned Swi>
struct swi<Swi, int( const void *, int )> {
    [[gnu::always_inline]]
    static int call( const void * arg0, int arg1 ) {
        int result;
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "movs\tr1, %[r1]\n\t"
        "swi\t%[Swi]\n\t"
        "movs\t%[out], r0"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "mov\tr1, %[r1]\n\t"
        "swi\t%[Swi] << 16\n\t"
        "mov\t%[out], r0"
#endif
        : [out]"+r"( result ) : [Swi]"i"( Swi ), [r0]"r"( arg0 ), [r1]"r"( arg1 ) : "r0", "r1", "r3"
        );
        return result;
    }
};

template <unsigned Swi>
struct swi<Swi, void( const void *, void * )> {
    [[gnu::always_inline]]
    static void call( const void * arg0, void * arg1 ) {
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "movs\tr1, %[r1]\n\t"
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "mov\tr1, %[r1]\n\t"
        "swi\t%[Swi] << 16"
#endif
        :: [Swi]"i"( Swi ), [r0]"r"( arg0 ), [r1]"r"( arg1 ) : "r0", "r1", "r3"
        );
    }
};

template <unsigned Swi>
struct swi<Swi, unsigned int( const void *, unsigned char, unsigned char )> {
    [[gnu::always_inline]]
    static unsigned int call( const void * arg0, unsigned char arg1, unsigned char arg2 ) {
        unsigned int result;
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "movs\tr1, %[r1]\n\t"
        "movs\tr2, %[r2]\n\t"
        "swi\t%[Swi]\n\t"
        "movs\t%[out], r0"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "mov\tr1, %[r1]\n\t"
        "mov\tr2, %[r2]\n\t"
        "swi\t%[Swi] << 16\n\t"
        "mov\t%[out], r0"
#endif
        : [out]"+r"( result ) : [Swi]"i"( Swi ), [r0]"r"( arg0 ), [r1]"r"( arg1 ), [r2]"r"( arg2 ) : "r0", "r1", "r2", "r3"
        );
        return result;
    }
};

template <unsigned Swi>
struct swi<Swi, void( const void *, void *, unsigned int )> {
    [[gnu::always_inline]]
    static void call( const void * arg0, void * arg1, unsigned int arg2 ) {
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "movs\tr1, %[r1]\n\t"
        "movs\tr2, %[r2]\n\t"
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "mov\tr1, %[r1]\n\t"
        "mov\tr2, %[r2]\n\t"
        "swi\t%[Swi] << 16"
#endif
        :: [Swi]"i"( Swi ), [r0]"r"( arg0 ), [r1]"r"( arg1 ), [r2]"r"( arg2 ) : "r0", "r1", "r2", "r3"
        );
    }
};

template <unsigned Swi>
struct swi<Swi, void( const void *, void *, unsigned int, unsigned int )> {
    [[gnu::always_inline]]
    static void call( const void * arg0, void * arg1, unsigned int arg2, unsigned int arg3 ) {
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "movs\tr1, %[r1]\n\t"
        "movs\tr2, %[r2]\n\t"
        "movs\tr3, %[r3]\n\t"
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "mov\tr1, %[r1]\n\t"
        "mov\tr2, %[r2]\n\t"
        "mov\tr3, %[r3]\n\t"
        "swi\t%[Swi] << #16"
#endif
        :: [Swi]"i"( Swi ), [r0]"r"( arg0 ), [r1]"r"( arg1 ), [r2]"r"( arg2 ), [r3]"r"( arg3 ) : "r0", "r1", "r2", "r3"
        );
    }
};

template <unsigned Swi>
struct swi<Swi, void( const void *, void *, const void * )> {
    [[gnu::always_inline]]
    static void call( const void * arg0, void * arg1, const void * arg2 ) {
        asm(
#if defined( __thumb__ )
        "movs\tr0, %[r0]\n\t"
        "movs\tr1, %[r1]\n\t"
        "movs\tr2, %[r2]\n\t"
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "mov\tr0, %[r0]\n\t"
        "mov\tr1, %[r1]\n\t"
        "mov\tr2, %[r2]\n\t"
        "swi\t%[Swi] << #16"
#endif
        :: [Swi]"i"( Swi ), [r0]"r"( arg0 ), [r1]"r"( arg1 ), [r2]"r"( arg2 ) : "r0", "r1", "r2", "r3"
        );
    }
};

} // bios
} // gba

#endif // define GBAXX_BIOS_SWI_HPP
