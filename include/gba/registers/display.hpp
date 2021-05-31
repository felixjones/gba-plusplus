#ifndef GBAXX_REGISTERS_DISPLAY_HPP
#define GBAXX_REGISTERS_DISPLAY_HPP

#include <gba/display/background_control.hpp>
#include <gba/display/color_blend.hpp>
#include <gba/display/display_control.hpp>
#include <gba/display/interrupt_status.hpp>
#include <gba/display/mosaic.hpp>
#include <gba/display/window.hpp>
#include <gba/types/fixed_point.hpp>
#include <gba/types/fixed_point_make.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/memmap.hpp>

namespace gba {
namespace reg {

using dispcnt = iomemmap<display_control, 0x4000000>;
using dispstat = iomemmap<display_status, 0x4000004>;
using vcount = imemmap<uint16, 0x4000006>;

using bg0cnt = iomemmap<background_control, 0x4000008>;
using bg1cnt = iomemmap<background_control, 0x400000a>;
using bg2cnt = iomemmap<background_control, 0x400000c>;
using bg3cnt = iomemmap<background_control, 0x400000e>;

using bg0hofs = omemmap<int16, 0x4000010>;
using bg0vofs = omemmap<int16, 0x4000012>;

using bg1hofs = omemmap<int16, 0x4000014>;
using bg1vofs = omemmap<int16, 0x4000016>;

using bg2hofs = omemmap<int16, 0x4000018>;
using bg2vofs = omemmap<int16, 0x400001a>;

using bg3hofs = omemmap<int16, 0x400001c>;
using bg3vofs = omemmap<int16, 0x400001e>;

using bg2pa = omemmap<make_fixed<7, 8>, 0x4000020>;
using bg2pb = omemmap<make_fixed<7, 8>, 0x4000022>;
using bg2pc = omemmap<make_fixed<7, 8>, 0x4000024>;
using bg2pd = omemmap<make_fixed<7, 8>, 0x4000026>;
using bg2x = omemmap<make_fixed<19, 8>, 0x4000028>;
using bg2y = omemmap<make_fixed<19, 8>, 0x400002c>;

using bg3pa = omemmap<make_fixed<7, 8>, 0x4000030>;
using bg3pb = omemmap<make_fixed<7, 8>, 0x4000032>;
using bg3pc = omemmap<make_fixed<7, 8>, 0x4000034>;
using bg3pd = omemmap<make_fixed<7, 8>, 0x4000036>;
using bg3x = omemmap<make_fixed<19, 8>, 0x4000038>;
using bg3y = omemmap<make_fixed<19, 8>, 0x400003c>;

using win0h = omemmap<window_dimension, 0x4000040>;
using win1h = omemmap<window_dimension, 0x4000042>;
using win0v = omemmap<window_dimension, 0x4000044>;
using win1v = omemmap<window_dimension, 0x4000046>;

using winin = iomemmap<window_control, 0x4000048>;
using winout = iomemmap<window_control, 0x400004a>;

using mosaic = omemmap<mosaic_size, 0x400004c>;

using bldcnt = iomemmap<blend_control, 0x4000050>;
using bldalpha = iomemmap<blend_alpha, 0x4000052>;
using bldy = omemmap<make_ufixed<28, 4>, 0x4000054>;

using bldgamma = omemmap<make_ufixed<28, 4>, 0x4000054>;

namespace undocumented {

using green_swap = iomemmap<gba::undocumented::green_swap, 0x4000002>;

} // undocumented
} // reg
} // gba

#endif // define GBAXX_REGISTERS_DISPLAY_HPP
