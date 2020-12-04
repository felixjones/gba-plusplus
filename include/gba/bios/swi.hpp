#ifndef GBAXX_BIOS_SWI_HPP
#define GBAXX_BIOS_SWI_HPP

namespace gba {
namespace bios {

template <unsigned Swi, class Function>
struct swi;

template <unsigned Swi>
struct swi<Swi, void( void )> {
    [[gnu::always_inline]]
    static void call() noexcept {
        asm inline (
#if defined( __thumb__ )
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "swi\t%[Swi] << 16"
#endif
        :: [Swi]"i"( Swi )
        );
    }

    [[gnu::always_inline]]
    static void clobber_call_0_1() noexcept {
        asm inline (
#if defined( __thumb__ )
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "swi\t%[Swi] << 16"
#endif
        :: [Swi]"i"( Swi ) : "r0", "r1"
        );
    }
};

template <unsigned Swi>
struct swi<Swi, void( int )> {
    [[gnu::always_inline]]
    static void call_r2( int&& arg0 ) noexcept {
        asm inline (
        "mov\tr2, %[arg0]\n\t"
        #if defined( __thumb__ )
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "swi\t%[Swi] << 16"
#endif
        :: [Swi]"i"( Swi ), [arg0]"ri"( arg0 ) : "r2"
        );
    }
};

template <unsigned Swi>
struct swi<Swi, void( int, int )> {
    [[gnu::always_inline]]
    static void call( int&& arg0, int&& arg1 ) noexcept {
        asm inline (
        "mov\tr0, %[arg0]\n\t"
        "mov\tr1, %[arg1]\n\t"
        #if defined( __thumb__ )
        "swi\t%[Swi]"
#elif defined( __arm__ )
        "swi\t%[Swi] << 16"
#endif
        :: [Swi]"i"( Swi ), [arg0]"ri"( arg0 ), [arg1]"ri"( arg1 ) : "r0", "r1"
        );
    }
};

} // bios
} // gba

#endif // define GBAXX_BIOS_SWI_HPP
