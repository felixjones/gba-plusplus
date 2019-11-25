#ifndef GBAXX_IO_SYSTEM_HPP
#define GBAXX_IO_SYSTEM_HPP

#include <gba/bit_bool.hpp>
#include <gba/int.hpp>
#include <gba/io_reg.hpp>
#include <gba/waitstate.hpp>

namespace gba {
namespace io {

namespace system {

static reg<gba::waitstate::control>& waitstate = *reinterpret_cast<reg<gba::waitstate::control> *>( 0x4000204 );

namespace undocumented {

	static reg<bit_bool<uint8>>&	post_flag = *reinterpret_cast<reg<bit_bool<uint8>> *>( 0x4000300 );
	static reg<bit_bool<uint8, 7>>&	halt_control = *reinterpret_cast<reg<bit_bool<uint8, 7>> *>( 0x4000301 );
	static reg<uint8>&				unknown_4000410 = *reinterpret_cast<reg<uint8> *>( 0x4000410 );

	static reg<gba::waitstate::wram_control>& wram_control = *reinterpret_cast<reg<gba::waitstate::wram_control> *>( 0x4000800 );

} // undocumented

} // system

} // io
} // gba

#endif // define GBAXX_IO_SYSTEM_HPP