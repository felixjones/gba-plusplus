#ifndef GBAXX_DISPLAY_HPP
#define GBAXX_DISPLAY_HPP

#include <gba/int.hpp>

namespace gba {
namespace display {

struct control_setting {

	uint16	mode : 3;

	const uint16	is_game_boy : 1;

	uint16	page : 1;
	uint16	unlock_oam_hblank : 1;
	uint16	linear_object_mapping : 1;
	uint16	forced_blank : 1;
	uint16	background_layers : 4;
	uint16	object_layer : 1;
	uint16	background_windows : 2;
	uint16	object_window : 1;

} __attribute__((packed));

class control : public control_setting {
public:

	constexpr control() : control_setting {} {}

	control( const volatile control& other ) : control_setting {} {
		*( ( uint16 * )this ) = *( ( const uint16 * )&other );
	}

	void operator=( const control_setting& other ) volatile {
		*( ( volatile uint16 * )this ) = *( ( const uint16 * )&other );
	}

};

struct status {

	const uint8	in_vertical_blank : 1;
	const uint8	in_horizontal_blank : 1;
	const uint8	in_vertical_counter : 1;
	uint8	irq_vertical_blank : 1;
	uint8	irq_horizontal_blank : 1;
	uint8	irq_vertical_counter : 1;

	uint8	vertical_counter_line;

} __attribute__( ( packed ) );

using vertical_counter = uint16;

} // display
} // gba

#endif // define GBAXX_DISPLAY_HPP
