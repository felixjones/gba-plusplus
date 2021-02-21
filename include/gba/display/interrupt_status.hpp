#ifndef GBAXX_DISPLAY_INTERRUPT_STATUS_HPP
#define GBAXX_DISPLAY_INTERRUPT_STATUS_HPP

#include <gba/types/int_type.hpp>

namespace gba {

struct display_status {
    const bool in_vblank : 1,
            in_hblank : 1,
            in_vcount : 1;
    bool vblank_irq : 1,
            hblank_irq : 1,
            vcount_irq : 1;
    uint8 vcount_setting;
};

static_assert( sizeof( display_status ) == 2, "display_status must be tightly packed" );

} // gba

#endif // define GBAXX_DISPLAY_INTERRUPT_STATUS_HPP
