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
/**
 * GBA memory mapped registers
 */
namespace reg {

/// 4000000h REG_DISPCNT \ref display_control
using dispcnt = iomemmap<display_control, 0x4000000>;
/// 4000004h REG_DISPSTAT \ref display_status
using dispstat = iomemmap<display_status, 0x4000004>;
/// 4000006h REG_VCOUNT
using vcount = imemmap<uint16, 0x4000006>;

/// 4000008h REG_BG0CNT \ref background_control
using bg0cnt = iomemmap<background_control, 0x4000008>;
/// 400000Ah REG_BG1CNT \ref background_control
using bg1cnt = iomemmap<background_control, 0x400000a>;
/// 400000Ch REG_BG2CNT \ref background_control
using bg2cnt = iomemmap<background_control, 0x400000c>;
/// 400000Eh REG_BG3CNT \ref background_control
using bg3cnt = iomemmap<background_control, 0x400000e>;

/// 4000010h REG_BG0HOFS
using bg0hofs = omemmap<int16, 0x4000010>;
/// 4000012h REG_BG0VOFS
using bg0vofs = omemmap<int16, 0x4000012>;

/// 4000014h REG_BG1HOFS
using bg1hofs = omemmap<int16, 0x4000014>;
/// 4000016h REG_BG1VOFS
using bg1vofs = omemmap<int16, 0x4000016>;

/// 4000018h REG_BG2HOFS
using bg2hofs = omemmap<int16, 0x4000018>;
/// 400001Ah REG_BG2VOFS
using bg2vofs = omemmap<int16, 0x400001a>;

/// 400001Ch REG_BG3HOFS
using bg3hofs = omemmap<int16, 0x400001c>;
/// 400001Eh REG_BG3VOFS
using bg3vofs = omemmap<int16, 0x400001e>;

/// 4000020h REG_BG2PA \ref gba::fixed_point
using bg2pa = omemmap<make_fixed<7, 8>, 0x4000020>;
/// 4000022h REG_BG2PB \ref gba::fixed_point
using bg2pb = omemmap<make_fixed<7, 8>, 0x4000022>;
/// 4000024h REG_BG2PC \ref gba::fixed_point
using bg2pc = omemmap<make_fixed<7, 8>, 0x4000024>;
/// 4000026h REG_BG2PD \ref gba::fixed_point
using bg2pd = omemmap<make_fixed<7, 8>, 0x4000026>;
/// 4000028h REG_BG2X \ref gba::fixed_point
using bg2x = omemmap<make_fixed<19, 8>, 0x4000028>;
/// 400002Ch REG_BG2Y \ref gba::fixed_point
using bg2y = omemmap<make_fixed<19, 8>, 0x400002c>;

/// 4000030h REG_BG3PA \ref gba::fixed_point
using bg3pa = omemmap<make_fixed<7, 8>, 0x4000030>;
/// 4000032h REG_BG3PB \ref gba::fixed_point
using bg3pb = omemmap<make_fixed<7, 8>, 0x4000032>;
/// 4000034h REG_BG3PC \ref gba::fixed_point
using bg3pc = omemmap<make_fixed<7, 8>, 0x4000034>;
/// 4000036h REG_BG3PD \ref gba::fixed_point
using bg3pd = omemmap<make_fixed<7, 8>, 0x4000036>;
/// 4000038h REG_BG3X \ref gba::fixed_point
using bg3x = omemmap<make_fixed<19, 8>, 0x4000038>;
/// 400003Ch REG_BG3Y \ref gba::fixed_point
using bg3y = omemmap<make_fixed<19, 8>, 0x400003c>;

/// 4000040h REG_WIN0H \ref gba::window_dimension
using win0h = omemmap<window_dimension, 0x4000040>;
/// 4000042h REG_WIN1H \ref gba::window_dimension
using win1h = omemmap<window_dimension, 0x4000042>;
/// 4000044h REG_WIN0V \ref gba::window_dimension
using win0v = omemmap<window_dimension, 0x4000044>;
/// 4000062h REG_WIN1V \ref gba::window_dimension
using win1v = omemmap<window_dimension, 0x4000046>;

/// 4000048h REG_WININ \ref gba::window_control
using winin = iomemmap<window_control, 0x4000048>;
/// 400004Ah REG_WINOUT \ref gba::window_control
using winout = iomemmap<window_control, 0x400004a>;

/// 400004Ch REG_MOSAIC \ref gba::mosaic_size
using mosaic = omemmap<mosaic_size, 0x400004c>;

/// 4000050h REG_BLDCNT \ref gba::blend_control
using bldcnt = iomemmap<blend_control, 0x4000050>;
/// 4000052h REG_BLDALPHA \ref gba::blend_alpha
using bldalpha = iomemmap<blend_alpha, 0x4000052>;
/// 4000054h REG_BLDY \ref gba::fixed_point
using bldy = omemmap<make_ufixed<28, 4>, 0x4000054>;

/// 4000054h REG_BLDGAMMA (alias of REG_BLDY) \ref gba::fixed_point
using bldgamma = omemmap<make_ufixed<28, 4>, 0x4000054>;

/**
 * Undocumented display registers
 */
namespace undocumented {

/// 4000002h REG_GREEN_SWAP \ref gba::undocumented::green_swap
using green_swap = iomemmap<gba::undocumented::green_swap, 0x4000002>;

} // undocumented
} // reg
} // gba

#endif // define GBAXX_REGISTERS_DISPLAY_HPP
