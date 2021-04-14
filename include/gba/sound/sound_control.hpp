#ifndef GBAXX_SOUND_CONTROL_HPP
#define GBAXX_SOUND_CONTROL_HPP

namespace gba {
namespace sound {

struct stereo_volume {
    uint16 volume_right : 3,
        : 1;
    uint16 volume_left : 3,
        : 1;
    bool channel1_right : 1,
        channel2_right : 1,
        channel3_right : 1,
        channel4_right : 1,
        channel1_left : 1,
        channel2_left : 1,
        channel3_left : 1,
        channel4_left : 1;
};

static_assert( sizeof( stereo_volume ) == 2, "stereo_volume must be tightly packed" );

enum class dmg_volume : uint16 {
    quarter = 0,
    half = 1,
    full = 2
};

struct mixing {
    enum class dma_volume : bool {
        half = false,
        full = true
    };

    sound::dmg_volume dmg_volume : 2;
    dma_volume dma_a_volume : 1,
        dma_b_volume : 1;
    uint16 : 4;
    bool dma_a_enable_right : 1,
        dma_a_enable_left : 1;
    uint16 dma_a_timer : 1;
    bool dma_a_reset_fifo : 1,
        dma_b_enable_right : 1,
        dma_b_enable_left : 1;
    uint16 dma_b_timer : 1;
    bool dma_b_reset_fifo : 1;
};

static_assert( sizeof( mixing ) == 2, "mixing must be tightly packed" );

struct master_enable {
    bool channel1_enable : 1,
        channel2_enable : 1,
        channel3_enable : 1,
        channel4_enable : 1;
    uint32 : 3;
    bool fifo_enable : 1;
    uint32 : 24;
};

static_assert( sizeof( master_enable ) == 4, "master_enable must be tightly packed" );

struct bias_control {
    uint32 : 1,
        level : 9,
        : 4,
        amplitude : 2,
        : 16;
};

static_assert( sizeof( bias_control ) == 4, "bias_control must be tightly packed" );

} // sound
} // gba

#endif // define GBAXX_SOUND_CONTROL_HPP
