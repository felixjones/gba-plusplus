#ifndef GBAXX_VIDEO_TRAITS_HPP
#define GBAXX_VIDEO_TRAITS_HPP

namespace gba {
namespace video {

template <unsigned Mode>
struct mode_limits {};

template <>
struct mode_limits<3> {
	static constexpr auto width() {
		return 240;
	}

	static constexpr auto height() {
		return 160;
	}

	static constexpr auto bpp() {
		return 16;
	}

	static constexpr auto stride() {
		return 480;
	}

	static constexpr auto length() {
		return 76800;
	}
};

} // video

} // gba

#endif // define GBAXX_VIDEO_TRAITS_HPP