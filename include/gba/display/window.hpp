#ifndef GBAXX_DISPLAY_WINDOW_HPP
#define GBAXX_DISPLAY_WINDOW_HPP

#include <gba/types/int_type.hpp>
#include <gba/types/uint_size.hpp>

namespace gba {

struct window_dimension {
    uint_size8 end;
    uint8 begin;
};

static_assert( sizeof( window_dimension ) == 2, "window_dimension must be tightly packed" );

namespace {

[[nodiscard]]
constexpr window_dimension make_window_dimension( const uint32 origin, const uint32 size ) noexcept {
    return window_dimension { size, uint8( origin ) };
}

struct window_control {
    bool win0_bg0 : 1,
        win0_bg1 : 1,
        win0_bg2 : 1,
        win0_bg3 : 1,
        win0_obj : 1,
        win0_blend : 1;
    uint8 : 2;
    bool win1_bg0 : 1,
        win1_bg1 : 1,
        win1_bg2 : 1,
        win1_bg3 : 1,
        win1_obj : 1,
        win1_blend : 1;
    uint8 : 2;
};

static_assert( sizeof( window_control ) == 2, "window_control must be tightly packed" );

}
} // gba

#endif // define GBAXX_DISPLAY_WINDOW_HPP
