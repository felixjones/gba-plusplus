#ifndef GBAXX_TILE_HPP
#define GBAXX_TILE_HPP

#include <gba/int.hpp>

namespace gba {

struct tile_attribute {
	uint16	tile_id : 10;
	bool	h_flip : 1,
			v_flip : 1;
	uint8	palette : 4;
};

} // gba

#endif // define GBAXX_TILE_HPP
