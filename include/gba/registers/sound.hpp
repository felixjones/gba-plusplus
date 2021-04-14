#ifndef GBAXX_REGISTERS_SOUND_HPP
#define GBAXX_REGISTERS_SOUND_HPP

#include <gba/sound/duty_control.hpp>
#include <gba/sound/frequency_control.hpp>
#include <gba/sound/sound_control.hpp>
#include <gba/sound/sweep_control.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/memmap.hpp>

namespace gba {
namespace reg {

using sound1cnt_l = iomemmap<sound::sweep_control, 0x4000060>;
using sound1cnt_h = iomemmap<sound::duty_control, 0x4000062>;
using sound1cnt_x = iomemmap<sound::frequency, 0x4000064>;

using soundcnt_l = iomemmap<sound::stereo_volume, 0x4000080>;
using soundcnt_h = iomemmap<sound::mixing, 0x4000082>;
using soundcnt_x = iomemmap<sound::master_enable, 0x4000084>;
using soundbias = iomemmap<sound::bias_control, 0x4000088>;

} // reg
} // gba

#endif // define GBAXX_REGISTERS_SOUND_HPP
