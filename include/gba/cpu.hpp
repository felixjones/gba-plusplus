#ifndef GBAXX_CPU_HPP
#define GBAXX_CPU_HPP

namespace gba {
namespace cpu {

template <typename Type, unsigned Register>
struct iregister {};

template <typename Type, unsigned Register>
struct oregister {};

template <typename Type, unsigned Register>
class ioregister : public iregister<Type, Register>, public oregister<Type, Register> {};

#if defined( __thumb__ )
#define GBAXX_IREGISTER_READ( REG ) __asm__ volatile ( "movs\t%0, r"#REG : "=r"( x ) :: "cc" )
#else
#define GBAXX_IREGISTER_READ( REG ) __asm__ volatile ( "mov\t%0, r"#REG : "=r"( x ) )
#endif

#define GBAXX_IREGISTER( REG )\
template <typename Type>\
struct iregister<Type, REG> {\
	static auto read() noexcept {\
		Type x;\
		GBAXX_IREGISTER_READ( REG );\
		return x;\
	}\
}

#if defined( __thumb__ )
#define GBAXX_OREGISTER_WRITE( REG ) __asm__( "movs\tr"#REG", %0" :: "ri"( value ) : "r"#REG, "cc" )
#else
#define GBAXX_OREGISTER_WRITE( REG ) __asm__( "mov\tr"#REG", %0" :: "ri"( value ) : "r"#REG )
#endif

#define GBAXX_OREGISTER( REG )\
template <typename Type>\
struct oregister<Type, REG> {\
	static void write( const Type value ) noexcept {\
		GBAXX_OREGISTER_WRITE( REG );\
	}\
}

#define GBAXX_IOREGISTER( REG )\
	GBAXX_IREGISTER( REG );\
	GBAXX_OREGISTER( REG )

GBAXX_IOREGISTER( 0 );
GBAXX_IOREGISTER( 1 );
GBAXX_IOREGISTER( 2 );
GBAXX_IOREGISTER( 3 );
GBAXX_IOREGISTER( 4 );
GBAXX_IOREGISTER( 5 );
GBAXX_IOREGISTER( 6 );
GBAXX_IOREGISTER( 7 );

#undef GBAXX_IREGISTER
#undef GBAXX_IREGISTER_READ
#undef GBAXX_OREGISTER
#undef GBAXX_OREGISTER_WRITE
#undef GBAXX_IOREGISTER

} // cpu
} // gba

#endif // define GBAXX_CPU_HPP
