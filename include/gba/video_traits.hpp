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
		return 0x12C00;
	}

	static constexpr auto obj_start() {
		return 0x4000;
	}

};

template <>
struct mode_limits<4> {

	static constexpr auto width() {
		return 240;
	}

	static constexpr auto height() {
		return 160;
	}

	static constexpr auto bpp() {
		return 8;
	}

	static constexpr auto stride() {
		return 240;
	}

	static constexpr auto length() {
		return 0x9600;
	}

	static constexpr auto obj_start() {
		return 0x4000;
	}

};

template <>
struct mode_limits<5> {

	static constexpr auto width() {
		return 160;
	}

	static constexpr auto height() {
		return 128;
	}

	static constexpr auto bpp() {
		return 16;
	}

	static constexpr auto stride() {
		return 320;
	}

	static constexpr auto length() {
		return 0xA000;
	}

	static constexpr auto obj_start() {
		return 0x4000;
	}

};

} // video
} // gba

#endif // define GBAXX_VIDEO_TRAITS_HPP
