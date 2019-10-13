#ifndef GBAXX_COLOR_HPP
#define GBAXX_COLOR_HPP

#include <cstring>
#include <type_traits>

#include <gba/int.hpp>

namespace gba {

struct [[gnu::packed]] color {

	constexpr static color from_rgb24( uint32 rgb888 ) {
		return color {
			.red = static_cast<uint8>( ( rgb888 & 0xff0000 ) >> ( 16 + 3 ) ),
			.green = static_cast<uint8>( ( rgb888 & 0x00ff00 ) >> ( 8 + 3 ) ),
			.blue = static_cast<uint8>( ( rgb888 & 0x0000ff ) >> ( 0 + 3 ) )
		};
	}

	static color from_bgr15( uint16 bgr555 ) {
		color c;
		std::memcpy( &c, &bgr555, sizeof( bgr555 ) );
		return c;
	}

	uint16 to_uint16() const {
		return *( const uint16 * )this;
	}

	uint32 to_uint32() const {
		union {
			uint32 u32;
			uint16 u16[2];
		} v;
		v.u16[0] = to_uint16();
		v.u16[1] = to_uint16();
		return v.u32;
	}

	color rotl( unsigned s ) const {
		color c( *this );
		uint16 v;
		std::memcpy( &v, &c, sizeof( v ) );

		// MSB is always 0 at this point, so >> is fine
		v = ( v << s ) | ( v >> ( 15 - s ) );

		std::memcpy( &c, &v, sizeof( v ) );
		return c;
	}

	color rotr( unsigned s ) const {
		color c( *this );
		uint16 v;
		std::memcpy( &v, &c, sizeof( v ) );

		// MSB is always 0 at this point, so >> is fine
		v = ( v >> s ) | ( v << ( 15 - s ) );

		std::memcpy( &c, &v, sizeof( v ) );
		return c;
	}

	uint16	red : 5,
			green : 5,
			blue : 5;

};

} // gba

#endif // define GBAXX_COLOR_HPP