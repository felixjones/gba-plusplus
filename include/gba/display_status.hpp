#ifndef GBAXX_DISPLAY_STATUS_HPP
#define GBAXX_DISPLAY_STATUS_HPP

#include <gba/int.hpp>

namespace gba {

struct display_status {
	const bool	in_vblank : 1,
				in_hblank : 1,
				in_vcount : 1;

	bool	emit_vblank : 1,
			emit_hblank : 1,
			emit_vcount : 1;

	bool	: 2;

	uint16	vcount_line;
};

} // gba

#endif // define GBAXX_DISPLAY_STATUS_HPP
