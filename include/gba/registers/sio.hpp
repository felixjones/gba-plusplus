#ifndef GBAXX_REGISTERS_SIO_HPP
#define GBAXX_REGISTERS_SIO_HPP

#include <gba/sio/serial_control.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/memmap.hpp>

namespace gba {
namespace reg {

using siodata32 = iomemmap<uint32, 0x4000120>;

using siomulti0 = iomemmap<uint16, 0x4000120>;
using siomulti1 = iomemmap<uint16, 0x4000122>;
using siomulti2 = iomemmap<uint16, 0x4000124>;
using siomulti3 = iomemmap<uint16, 0x4000126>;

template <class Mode>
using siocnt = iomemmap<sio::control<Mode>, 0x4000128>;

using siodata8 = iomemmap<uint8, 0x400012A>;

using siomlt_send = iomemmap<uint16, 0x400012A>;

template <class Mode>
using rcnt = iomemmap<sio::r_control<Mode>, 0x4000134>;

using joycnt = iomemmap<joy_bus::control, 0x4000140>;
using joy_recv = iomemmap<uint32, 0x4000150>;
using joy_trans = iomemmap<uint32, 0x4000154>;
using joystat = iomemmap<joy_bus::status, 0x4000158>;

} // reg
} // gba

#endif // define GBAXX_REGISTERS_SIO_HPP
