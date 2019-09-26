#ifndef GBAXX_IO_INTERRUPT_HPP
#define GBAXX_IO_INTERRUPT_HPP

#include <gba/bit_bool.hpp>
#include <gba/int.hpp>
#include <gba/io_reg.hpp>
#include <gba/irq.hpp>

namespace gba {
namespace io {

namespace interrupt {

static volatile irq::handler_type& vector = *reinterpret_cast<volatile irq::handler_type *>( 0x3007FFC );

static reg<bit_bool<uint16>>& master_enable = *reinterpret_cast<reg<bit_bool<uint16>> *>( 0x4000208 );
static reg<irq::bits>& enable_mask = *reinterpret_cast<reg<irq::bits> *>( 0x4000200 );
static reg<irq::bits>& raised_flags = *reinterpret_cast<reg<irq::bits> *>( 0x4000202 );

} // interrupt

} // io
} // gba

#endif // define GBAXX_IO_INTERRUPT_HPP