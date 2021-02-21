#ifndef GBAXX_GBA_HPP
#define GBAXX_GBA_HPP

#include <gba/bios/affine.hpp>
#include <gba/bios/cpu_copy.hpp>
#include <gba/bios/halt.hpp>
#include <gba/bios/math.hpp>
#include <gba/bios/reset.hpp>
#include <gba/bios/swi.hpp>

#include <gba/display/display_control.hpp>
#include <gba/display/interrupt_status.hpp>

#include <gba/io/io.hpp>
#include <gba/io/mode0.hpp>
#include <gba/io/mode1.hpp>
#include <gba/io/mode2.hpp>
#include <gba/io/mode3.hpp>
#include <gba/io/mode4.hpp>
#include <gba/io/mode5.hpp>

#include <gba/keypad/keypad.hpp>
#include <gba/keypad/keypad_manager.hpp>

#include <gba/registers/display.hpp>
#include <gba/registers/interrupt_control.hpp>
#include <gba/registers/keypad_input.hpp>

#include <gba/types/bit_container.hpp>
#include <gba/types/fixed_point.hpp>
#include <gba/types/fixed_point_funcs.hpp>
#include <gba/types/fixed_point_make.hpp>
#include <gba/types/fixed_point_operators.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/interrupt_mask.hpp>
#include <gba/types/memmap.hpp>

#endif // define GBAXX_GBA_HPP
