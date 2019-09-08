#ifndef GBAXX_VIDEO_HPP
#define GBAXX_VIDEO_HPP

#include <gba/int.hpp>

namespace gba {
namespace video {

namespace bitmap {

using buffer = uint16[0x5000];

static buffer * const	frame_buffer = reinterpret_cast<buffer *>( 0x06000000 );

} // bitmap

} // video
} // gba

#endif // define GBAXX_VIDEO_HPP