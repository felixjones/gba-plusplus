#ifndef GBAXX_COLOR_HPP
#define GBAXX_COLOR_HPP

#include <cstring>

#include <gba/int.hpp>

namespace gba {

struct [[gnu::packed]] color {

	template <unsigned Value>
	constexpr static color from_rgb24() {
		return color {
			.blue = static_cast< uint8 >( ( Value & 0x0000f8 ) >> 3 ),
			.green = static_cast< uint8 >( ( Value & 0x00f800 ) >> 11 ),
			.red = static_cast< uint8 >( ( Value & 0xf80000 ) >> 19 )
		};
	}

	constexpr static color from_rgb24( uint24 rgb888 ) {
		return color {
			.blue = static_cast<uint8>( ( rgb888 & 0x0000f8 ) >> 3 ),
			.green = static_cast<uint8>( ( rgb888 & 0x00f800 ) >> 11 ),
			.red = static_cast<uint8>( ( rgb888 & 0xf80000 ) >> 19 )
		};
	}

	static color from_rgb15( uint16 rgb555 ) {
		color c;
		std::memcpy( &c, &rgb555, sizeof( rgb555 ) );
		return c;
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

	uint16	: 1,
			blue : 5,
			green : 5,
			red : 5;

};

} // gba

#endif // define GBAXX_COLOR_HPP