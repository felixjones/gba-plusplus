#ifndef GBAXX_VIDEO_BUFFER_HPP
#define GBAXX_VIDEO_BUFFER_HPP

#include <gba/color.hpp>

namespace gba {
namespace video {

template <unsigned Mode>
struct mode_buffer {};

template <>
struct mode_buffer<3> {

	static color * ptr() {
		return reinterpret_cast<color *>( 0x6000000 );
	}

};

// video::mode<3>::page( 0 )

} // video
} // gba

#endif // define GBAXX_VIDEO_BUFFER_HPP