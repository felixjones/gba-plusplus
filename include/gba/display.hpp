#ifndef GBAXX_DISPLAY_HPP
#define GBAXX_DISPLAY_HPP

#include <gba/int.hpp>

namespace gba {
namespace display {

struct [[gnu::packed]] control {

	uint8	mode : 3,
			: 1;

	bool	page : 1,
			unlock_oam_hblank : 1,
			linear_object_mapping : 1,
			forced_blank : 1,
			background_layer0 : 1,
			background_layer1 : 1,
			background_layer2 : 1,
			background_layer3 : 1,
			object_layer : 1,
			background_window0 : 1,
			background_window1 : 1,
			object_window : 1;

};

struct [[gnu::packed]] status {

	const bool	in_vblank : 1,
				in_hblank : 1,
				in_vcount : 1;

	bool	emit_vblank : 1,
			emit_hblank : 1,
			emit_vcount : 1;

	const bool	: 1;
	bool		: 1;

	uint16	vcount_line;

};

} // display
} // gba

#endif // define GBAXX_DISPLAY_HPP
