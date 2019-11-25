#ifndef GBAXX_IO_SOUND_HPP
#define GBAXX_IO_SOUND_HPP

#include <gba/bit_bool.hpp>
#include <gba/int.hpp>
#include <gba/io_reg.hpp>
#include <gba/sound.hpp>

namespace gba {
namespace io {

namespace sound {

static reg<gba::sound::stereo_control>&	stereo_control = *reinterpret_cast<reg<gba::sound::stereo_control> *>( 0x4000080 );
static reg<gba::sound::mix_control>&	mix_control = *reinterpret_cast<reg<gba::sound::mix_control> *>( 0x4000082 );
static reg<gba::sound::master_control>&	master_control = *reinterpret_cast<reg<gba::sound::master_control> *>( 0x4000084 );

static reg<gba::sound::sweep>&		channel_1_sweep = *reinterpret_cast<reg<gba::sound::sweep> *>( 0x4000060 );
static reg<gba::sound::frequency>&	channel_1_frequency = *reinterpret_cast<reg<gba::sound::frequency> *>( 0x4000064 );

static reg<gba::sound::duty_envelope>&	channel_1_duty_envelope = *reinterpret_cast<reg<gba::sound::duty_envelope> *>( 0x4000062 );

} // sound

} // io
} // gba

#endif // define GBAXX_IO_SOUND_HPP
