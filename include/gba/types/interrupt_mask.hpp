#ifndef GBAXX_TYPES_INTERRUPT_MASK_HPP
#define GBAXX_TYPES_INTERRUPT_MASK_HPP

namespace gba {

struct interrupt_mask {
    bool vblank : 1,
            hblank : 1,
            vcount : 1,
            timer_0 : 1,
            timer_1 : 1,
            timer_2 : 1,
            timer_3 : 1,
            serial : 1,
            dma_0 : 1,
            dma_1 : 1,
            dma_2 : 1,
            dma_3 : 1,
            keypad : 1,
            gamepak : 1;
};

static_assert( sizeof( interrupt_mask ) == 2, "interrupt_mask must be tightly packed" );

} // gba

#endif // define GBAXX_TYPES_INTERRUPT_MASK_HPP
