#ifndef GBAXX_REGISTERS_SOUND_HPP
#define GBAXX_REGISTERS_SOUND_HPP

#include <gba/sound/direct.hpp>
#include <gba/sound/dmg.hpp>
#include <gba/sound/sound.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/memmap.hpp>

namespace gba {
namespace reg {

// Tonc names
using snd1sweep = iomemmap<sound::sweep, 0x4000060>;
using snd1cnt = iomemmap<sound::square_control, 0x4000062>;
using snd1freq = iomemmap<sound::square_frequency, 0x4000064>;

using snd2cnt = iomemmap<sound::square_control, 0x4000068>;
using snd2freq = iomemmap<sound::square_frequency, 0x400006c>;

using snd3sel = iomemmap<sound::wave_select, 0x4000070>;
using snd3cnt = iomemmap<sound::wave_control, 0x4000072>;
using snd3freq = iomemmap<sound::wave_frequency, 0x4000074>;

using snd4cnt = iomemmap<sound::noise_control, 0x4000078>;
using snd4freq = iomemmap<sound::noise_frequency, 0x400007c>;

using snddmgcnt = iomemmap<sound::dmg_control, 0x4000080>;
using snddscnt = iomemmap<sound::directsound_control, 0x4000082>;
using sndstat = iomemmap<sound::status, 0x4000084>;

using sdbias = iomemmap<sound::bias_control, 0x4000088>;

// New names
using sound1cnt_l = iomemmap<sound::sweep, 0x4000060>;
using sound1cnt_h = iomemmap<sound::square_control, 0x4000062>;
using sound1cnt_x = iomemmap<sound::square_frequency, 0x4000064>;

using sound2cnt_l = iomemmap<sound::square_control, 0x4000068>;
using sound2cnt_h = iomemmap<sound::square_frequency, 0x400006c>;

using sound3cnt_l = iomemmap<sound::wave_select, 0x4000070>;
using sound3cnt_h = iomemmap<sound::wave_control, 0x4000072>;
using sound3cnt_x = iomemmap<sound::wave_frequency, 0x4000074>;

using sound4cnt_l = iomemmap<sound::noise_control, 0x4000078>;
using sound4cnt_h = iomemmap<sound::noise_frequency, 0x400007c>;

using soundcnt_l = iomemmap<sound::dmg_control, 0x4000080>;
using soundcnt_h = iomemmap<sound::directsound_control, 0x4000082>;
using soundcnt_x = iomemmap<sound::status, 0x4000084>;

using soundbias = iomemmap<sound::bias_control, 0x4000088>;

using wave_ram = iomemmap<sound::wave_ram, 0x4000090>;

using fifo_a = iomemmap<uint32, 0x40000A0>;
using fifo_b = iomemmap<uint32, 0x40000A4>;

} // reg
} // gba

#endif // define GBAXX_REGISTERS_SOUND_HPP
