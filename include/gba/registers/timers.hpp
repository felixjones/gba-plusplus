#ifndef GBAXX_REGISTERS_TIMERS_HPP
#define GBAXX_REGISTERS_TIMERS_HPP

#include <gba/time/timer_control.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/memmap.hpp>

namespace gba {
namespace reg {

using tm0d = iomemmap<uint16, 0x4000100>;
using tm1d = iomemmap<uint16, 0x4000104>;
using tm2d = iomemmap<uint16, 0x4000108>;
using tm3d = iomemmap<uint16, 0x400010c>;

using tm0cnt = iomemmap<timer_control, 0x4000102>;
using tm1cnt = iomemmap<timer_control, 0x4000106>;
using tm2cnt = iomemmap<timer_control, 0x400010a>;
using tm3cnt = iomemmap<timer_control, 0x400010e>;

using tm0d_cnt = iomemmap<timer_counter_control, 0x4000100>;
using tm1d_cnt = iomemmap<timer_counter_control, 0x4000104>;
using tm2d_cnt = iomemmap<timer_counter_control, 0x4000108>;
using tm3d_cnt = iomemmap<timer_counter_control, 0x400010c>;

} // reg
} // gba

#endif // define GBAXX_REGISTERS_TIMERS_HPP
