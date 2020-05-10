#ifndef GBAXX_OAM_HPP
#define GBAXX_OAM_HPP

#include <gba/int.hpp>

namespace gba {
namespace oam {

} // oam

struct object_attribute0 {
	uint8	y : 8;
	uint8	obj_mode : 2,
			gfx_mode : 2;
	bool	mosaic : 1,
			hi_color : 1;
	uint8	shape : 2;
};

struct object_attribute1 {
	uint16	x : 9,
			matrix : 5,
			size : 2;
};

struct object_attribute2 {
	uint16	tile : 10,
			priority : 2,
			palette : 4;
};

struct object_attribute {
	object_attribute0	attr0;
	object_attribute1	attr1;
	object_attribute2	attr2;
};

} // gba

#endif // define GBAXX_OAM_HPP