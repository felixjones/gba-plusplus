#ifndef GBAXX_VIDEO_DISPLAY_STATUS_HPP
#define GBAXX_VIDEO_DISPLAY_STATUS_HPP

#include <gba/types/int_type.hpp>

namespace gba {

/**
 *
 */
struct display_status {
    const bool in_vertical_blank : 1,
            in_horizontal_blank : 1,
            in_vertical_count : 1;
    bool vertical_blank_irq : 1,
            horizontal_block_irq : 1,
            vertical_count_irq : 1;
    uint8 vertical_count_trigger;
};

static_assert( sizeof( display_status ) == 2, "display_status must be tightly packed" );

} // gba

#endif // define GBAXX_VIDEO_DISPLAY_STATUS_HPP
