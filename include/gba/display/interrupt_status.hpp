#ifndef GBAXX_DISPLAY_INTERRUPT_STATUS_HPP
#define GBAXX_DISPLAY_INTERRUPT_STATUS_HPP

#include <gba/types/int_type.hpp>

namespace gba {

/**
 * Interrupt status type
 */
struct display_status {
    const bool in_vblank : 1, ///< Is program in VBlank IRQ
            in_hblank : 1, ///< Is program in HBlank IRQ
            in_vcount : 1; ///< Is program in VCount IRQ
    bool vblank_irq : 1, ///< Enable VBlank IRQ
            hblank_irq : 1, ///< Enable HBlank IRQ
            vcount_irq : 1; ///< Enable VCount IRQ
    uint8 vcount_setting; ///< VCount line to trigger IRQ
};

static_assert( sizeof( display_status ) == 2, "display_status must be tightly packed" );

} // gba

#endif // define GBAXX_DISPLAY_INTERRUPT_STATUS_HPP
