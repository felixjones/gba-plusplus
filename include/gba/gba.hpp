#ifndef GBAXX_GBA_HPP
#define GBAXX_GBA_HPP

/**
 * Major version
 */
#define GBAXX_VERSION_MAJOR 0
/**
 * Minor version
 */
#define GBAXX_VERSION_MINOR 0
/**
 * Patch version
 */
#define GBAXX_VERSION_PATCH 4
/**
 * Combined version number
 *
 * Calculated as:
 * \code
 * ( GBAXX_VERSION_MAJOR * 10000 ) + ( GBAXX_VERSION_MINOR * 100 ) + ( GBAXX_VERSION_PATCH * 1 )
 * \endcode
 */
#define GBAXX_VERSION ( GBAXX_VERSION_MAJOR * 10000 ) + ( GBAXX_VERSION_MINOR * 100 ) + GBAXX_VERSION_PATCH

#include <gba/allocator/bitset_types.hpp>
#include <gba/allocator/buffer.hpp>
#include <gba/allocator/mode0.hpp>
#include <gba/allocator/mode1.hpp>
#include <gba/allocator/mode2.hpp>
#include <gba/allocator/mode3.hpp>
#include <gba/allocator/mode4.hpp>
#include <gba/allocator/mode5.hpp>
#include <gba/allocator/oam.hpp>
#include <gba/allocator/object_tile.hpp>
#include <gba/allocator/palette.hpp>
#include <gba/allocator/screen_affine.hpp>
#include <gba/allocator/screen_regular.hpp>
#include <gba/allocator/tile_4bpp.hpp>
#include <gba/allocator/tile_4bpp_2d.hpp>
#include <gba/allocator/tile_8bpp.hpp>
#include <gba/allocator/tile_8bpp_2d.hpp>
#include <gba/allocator/vram.hpp>

#include <gba/bios/affine.hpp>
#include <gba/bios/compression.hpp>
#include <gba/bios/cpu_copy.hpp>
#include <gba/bios/halt.hpp>
#include <gba/bios/huff.hpp>
#include <gba/bios/lz77.hpp>
#include <gba/bios/math.hpp>
#include <gba/bios/reset.hpp>
#include <gba/bios/rle.hpp>
#include <gba/bios/sound.hpp>
#include <gba/bios/swi.hpp>
#include <gba/bios/system.hpp>

#include <gba/display/background_control.hpp>
#include <gba/display/color_blend.hpp>
#include <gba/display/display_control.hpp>
#include <gba/display/interrupt_status.hpp>
#include <gba/display/mosaic.hpp>
#include <gba/display/window.hpp>

#include <gba/dma/dma_control.hpp>

#include <gba/io/background_matrix.hpp>
#include <gba/io/background_mode.hpp>
#include <gba/io/io.hpp>
#include <gba/io/mode0.hpp>
#include <gba/io/mode1.hpp>
#include <gba/io/mode2.hpp>
#include <gba/io/mode3.hpp>
#include <gba/io/mode4.hpp>
#include <gba/io/mode5.hpp>

#include <gba/keypad/keypad.hpp>
#include <gba/keypad/keypad_manager.hpp>

#include <gba/object/attributes.hpp>

#include <gba/registers/display.hpp>
#include <gba/registers/dma.hpp>
#include <gba/registers/interrupt_control.hpp>
#include <gba/registers/keypad_input.hpp>
#include <gba/registers/sio.hpp>
#include <gba/registers/sound.hpp>
#include <gba/registers/system.hpp>
#include <gba/registers/timers.hpp>

#include <gba/sio/general_purpose.hpp>
#include <gba/sio/joy_bus.hpp>
#include <gba/sio/multiplayer.hpp>
#include <gba/sio/normal.hpp>
#include <gba/sio/serial_control.hpp>
#include <gba/sio/uart.hpp>

#include <gba/sound/direct.hpp>
#include <gba/sound/dmg.hpp>
#include <gba/sound/sound.hpp>

#include <gba/system/undocumented.hpp>
#include <gba/system/waitstate.hpp>

#include <gba/time/timer_control.hpp>
#include <gba/time/generate_timers.hpp>

#include <gba/types/matrix/mat2x2.hpp>
#include <gba/types/matrix/mat3x2.hpp>
#include <gba/types/matrix/mat3x3.hpp>
#include <gba/types/matrix/mat4x4.hpp>

#include <gba/types/vector/vec2.hpp>
#include <gba/types/vector/vec3.hpp>
#include <gba/types/vector/vec4.hpp>

#include <gba/types/dimension.hpp>
#include <gba/types/fixed_point.hpp>
#include <gba/types/fixed_point_funcs.hpp>
#include <gba/types/fixed_point_make.hpp>
#include <gba/types/fixed_point_operators.hpp>
#include <gba/types/int_cast.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/interrupt_mask.hpp>
#include <gba/types/matrix.hpp>
#include <gba/types/memmap.hpp>
#include <gba/types/screen_tile.hpp>
#include <gba/types/uint_size.hpp>
#include <gba/types/vector.hpp>

#endif // define GBAXX_GBA_HPP
