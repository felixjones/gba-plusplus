#ifndef GBAXX_DRAWING_COLOR_HPP
#define GBAXX_DRAWING_COLOR_HPP

#include <gba/types/int_type.hpp>

namespace gba {
namespace color {

struct rgb555 {
    uint16 red : 5;
    uint16 green : 5;
    uint16 blue : 5;
    uint16 : 1;
};

} // color
} // gba

#endif // define GBAXX_DRAWING_COLOR_HPP
