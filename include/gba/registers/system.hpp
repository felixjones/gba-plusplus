#ifndef GBAXX_REGISTERS_SYSTEM_HPP
#define GBAXX_REGISTERS_SYSTEM_HPP

#include <gba/system/undocumented.hpp>
#include <gba/system/waitstate.hpp>
#include <gba/types/memmap.hpp>

namespace gba {
namespace reg {

using waitcnt = iomemmap<waitstate::control, 0x4000204>;

namespace undocumented {

using postflg = iomemmap<gba::undocumented::post_flag, 0x4000300>;

using haltcnt = omemmap<gba::undocumented::halt_control, 0x4000301>;

using obj_center = omemmap<gba::undocumented::object_center, 0x4000410>;

using rommap = iomemmap<gba::undocumented::memory_map, 0x4000800>;

} // undocumented
} // reg
} // gba

#endif // define GBAXX_REGISTERS_SYSTEM_HPP
