#ifndef GBAXX_DRAWING_HPP
#define GBAXX_DRAWING_HPP

#include <gba/int.hpp>

namespace gba {
namespace drawing {

struct graphics {
	uint8	width;
	uint8	height;
	uint8	bpp;
	uint8	stride;
	void *	data;
};

template <unsigned Mode>
constexpr auto graphics_mode() {
	if constexpr ( Mode == 3 ) {
		return graphics { 240, 160, 16, 480, ( void * )0x6000000 };
	}
	// TODO : Return a constexpr graphics instance for a particular mode
}

} // drawing
} // gba

#endif // define GBAXX_DRAWING_HPP