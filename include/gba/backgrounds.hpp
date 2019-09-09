#ifndef GBAXX_BACKGROUNDS_HPP
#define GBAXX_BACKGROUNDS_HPP

#include <gba/int.hpp>

namespace gba {
namespace background {

struct control_setting {
	
	uint16	priority : 2,
		character_block : 2, 
		: 2, 
		mosaic : 1, 
		color_depth : 1, 
		screen_block : 5, 
		wrap : 1, 
		screen_size : 2;

} __attribute__((packed));

class control : public control_setting {
public:

	constexpr control() : control_setting {} {}

	control( const volatile control& other ) : control_setting {} {
		*( ( uint16 * )this ) = *( ( const uint16 * )& other );
	}

	void operator=( const control_setting& other ) volatile {
		*( ( volatile uint16 * )this ) = *( ( const uint16 * )& other );
	}

};

struct scroll_setting {

	uint16	x : 9, : 7;
	uint16	y : 9, : 7;

} __attribute__((packed));

class scroll : public scroll_setting {
public:

	constexpr scroll() : scroll_setting {} {}

	scroll( const volatile scroll& other ) : scroll_setting {} {
		*( ( uint32 * )this ) = *( ( const uint32 * )& other );
	}

	void operator=( const scroll_setting& other ) volatile {
		*( ( volatile uint32 * )this ) = *( ( const uint32 * )& other );
	}

};

} // background
} // gba

#endif // define GBAXX_BACKGROUNDS_HPP