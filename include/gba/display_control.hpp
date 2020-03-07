#ifndef GBAXX_DISPLAY_CONTROL_HPP
#define GBAXX_DISPLAY_CONTROL_HPP

#include <cstring>

#include <gba/memmap.hpp>
#include <gba/int.hpp>
#include <gba/bool.hpp>

namespace gba {

struct display_control {
	static constexpr display_control make( void( *f )( display_control& ) ) {
		display_control value {};
		f( value );
		return value;
	}

	uint8	mode : 3;

	const bool	is_cgb : 1;

	bool	page : 1,
			unlock_oam_hblank : 1,
			linear_object_mapping : 1,
			force_blank : 1,
			background_layer0 : 1,
			background_layer1 : 1,
			background_layer2 : 1,
			background_layer3 : 1,
			object_layer : 1,
			background_window0 : 1,
			background_window1 : 1,
			object_window : 1;
};

} // gba

#endif // define GBAXX_DISPLAY_CONTROL_HPP
