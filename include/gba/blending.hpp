#ifndef GBAXX_BLENDING_HPP
#define GBAXX_BLENDING_HPP

#include <gba/fixed_point.hpp>
#include <gba/int.hpp>

namespace gba {

struct blend_control {
	bool	src_background0 : 1,
			src_background1 : 1,
			src_background2 : 1,
			src_background3 : 1,
			src_object	: 1,
			src_backdrop : 1;

	uint8	effect : 2;

	bool	dst_background0 : 1,
			dst_background1 : 1,
			dst_background2 : 1,
			dst_background3 : 1,
			dst_object	: 1,
			dst_backdrop : 1;

	uint8 : 2;
};

struct blend_alpha {
	fixed_point<uint8, 4>	src;
	fixed_point<uint8, 4>	dst;
};

} // gba

#endif // define GBAXX_BLENDING_HPP