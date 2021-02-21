#ifndef GBAXX_REGISTERS_INTERRUPT_CONTROL_HPP
#define GBAXX_REGISTERS_INTERRUPT_CONTROL_HPP

#include <gba/types/int_type.hpp>
#include <gba/types/interrupt_mask.hpp>
#include <gba/types/memmap.hpp>

namespace gba {
namespace reg {

using ime = iomemmap<uint32, 0x4000208>;
using ie = iomemmap<interrupt_mask, 0x4000200>;
using if_ = iomemmap<interrupt_mask, 0x4000202>;

} // reg
} // gba

#endif // define GBAXX_REGISTERS_INTERRUPT_CONTROL_HPP
