#ifndef GBAXX_GBA_HPP
#define GBAXX_GBA_HPP

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
#include <gba/bios/cpu_copy.hpp>
#include <gba/bios/halt.hpp>
#include <gba/bios/math.hpp>
#include <gba/bios/reset.hpp>
#include <gba/bios/swi.hpp>

#include <gba/display/background_control.hpp>
#include <gba/display/color_blend.hpp>
#include <gba/display/display_control.hpp>
#include <gba/display/interrupt_status.hpp>
#include <gba/display/mosaic.hpp>
#include <gba/display/window.hpp>

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
#include <gba/registers/interrupt_control.hpp>
#include <gba/registers/keypad_input.hpp>
#include <gba/registers/sound.hpp>
#include <gba/registers/timers.hpp>

#include <gba/sound/dmg/channel1.hpp>

#include <gba/sound/duty_control.hpp>
#include <gba/sound/frequency_control.hpp>
#include <gba/sound/sound_control.hpp>
#include <gba/sound/sweep_control.hpp>

#include <gba/time/timer_control.hpp>

#include <gba/types/matrix/mat2x2.hpp>
#include <gba/types/matrix/mat3x2.hpp>
#include <gba/types/matrix/mat3x3.hpp>
#include <gba/types/matrix/mat4x4.hpp>

#include <gba/types/vector/vec2.hpp>
#include <gba/types/vector/vec3.hpp>
#include <gba/types/vector/vec4.hpp>

#include <gba/types/bit_container.hpp>
#include <gba/types/dimension.hpp>
#include <gba/types/fixed_point.hpp>
#include <gba/types/fixed_point_funcs.hpp>
#include <gba/types/fixed_point_make.hpp>
#include <gba/types/fixed_point_operators.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/interrupt_mask.hpp>
#include <gba/types/matrix.hpp>
#include <gba/types/memmap.hpp>
#include <gba/types/screen_tile.hpp>
#include <gba/types/uint_size.hpp>
#include <gba/types/vector.hpp>

#endif // define GBAXX_GBA_HPP
