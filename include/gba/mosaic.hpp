#ifndef GBAXX_MOSAIC_HPP
#define GBAXX_MOSAIC_HPP

#include <gba/int.hpp>

namespace gba {

struct mosaic_control {
	uint8	background_width : 4,
			background_height : 4,
			object_width : 4,
			object_height : 4;
};

} // gba

#endif // define GBAXX_MOSAIC_HPP
