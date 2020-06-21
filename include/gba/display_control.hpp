#ifndef GBAXX_DISPLAY_CONTROL_HPP
#define GBAXX_DISPLAY_CONTROL_HPP

#include <gba/int.hpp>

namespace gba {

struct display_control {
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
