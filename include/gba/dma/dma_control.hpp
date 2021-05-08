#ifndef GBAXX_DMA_DMA_CONTROL_HPP
#define GBAXX_DMA_DMA_CONTROL_HPP

#include <gba/types/int_type.hpp>

namespace gba {

struct dma_control {
    enum class destination_address : uint16 {
        increment = 0,
        decrement = 1,
        fixed = 2,
        increment_then_reload = 3,

        keep = fixed
    };

    enum class source_address : uint16 {
        increment = 0,
        decrement = 1,
        fixed = 2,

        keep = fixed
    };

    enum class type : bool {
        half = false,
        word = true
    };

    enum class start : uint16 {
        immediately = 0,
        next_vblank = 1,
        next_hblank = 2,
        sound_fifo = 3,
        next_scan_out = 3,

        now = immediately
    };

    uint16 : 5;
    destination_address destination_control : 2;
    source_address source_control : 2;
    bool repeat : 1;
    dma_control::type type : 1;
    bool gamepak_dma_request : 1;
    start start_condition : 2;
    bool irq_on_finish : 1;
    bool enable : 1;
};

static_assert( sizeof( dma_control ) == 2, "dma_control must be tightly packed" );

struct dma_transfer_control {
    uint16 transfers;
    dma_control control;
};

static_assert( sizeof( dma_transfer_control ) == 4, "dma_transfer_control must be tightly packed" );

} // gba

#endif // define GBAXX_DMA_DMA_CONTROL_HPP
