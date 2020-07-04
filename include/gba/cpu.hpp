#ifndef GBAXX_CPU_HPP
#define GBAXX_CPU_HPP

#include <type_traits>

namespace gba {
namespace cpu {

template <typename Type, unsigned Register>
struct iregister {};

template <typename Type>
struct iregister<Type, 0> {
	static auto read() noexcept {
		Type x;
#if defined( __thumb__ )
		__asm__( "movs\t%0, r0" : "=r"( x ) );
#else
		__asm__( "mov\t%0, r0" : "=r"( x ) );
#endif
		return x;
	}
};

template <typename Type>
struct iregister<Type, 1> {
	static auto read() noexcept {
		Type x;
#if defined( __thumb__ )
		__asm__( "movs\t%0, r1" : "=r"( x ) );
#else
		__asm__( "mov\t%0, r1" : "=r"( x ) );
#endif
		return x;
	}
};

template <typename Type>
struct iregister<Type, 2> {
	static auto read() noexcept {
		Type x;
#if defined( __thumb__ )
		__asm__( "movs\t%0, r2" : "=r"( x ) );
#else
		__asm__( "mov\t%0, r2" : "=r"( x ) );
#endif
		return x;
	}
};

template <typename Type>
struct iregister<Type, 3> {
	static auto read() noexcept {
		Type x;
#if defined( __thumb__ )
		__asm__( "movs\t%0, r3" : "=r"( x ) );
#else
		__asm__( "mov\t%0, r3" : "=r"( x ) );
#endif
		return x;
	}
};

} // cpu
} // gba

#endif // define GBAXX_CPU_HPP
