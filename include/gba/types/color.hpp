#ifndef GBAXX_TYPES_COLOR_HPP
#define GBAXX_TYPES_COLOR_HPP

namespace gba {

enum class color_depth : bool {
    color_16 = false,
    color_256 = true,
    bpp_4 = false,
    bpp_8 = true
};

} // gba

#endif // define GBAXX_TYPES_COLOR_HPP
