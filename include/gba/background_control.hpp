#ifndef GBAXX_BACKGROUND_CONTROL_HPP
#define GBAXX_BACKGROUND_CONTROL_HPP

#include <gba/int.hpp>

namespace gba {

struct background_control {
	uint8	priority : 2,
			character_base_block : 2;

	uint8	: 2;

	bool	mosaic : 1,
			high_color : 1;

	uint8	tilemap_base_block : 5;

	bool	affine_wrap : 1;

	uint8	size : 2;
};

} // gba

#endif // define GBAXX_BACKGROUND_CONTROL_HPP
