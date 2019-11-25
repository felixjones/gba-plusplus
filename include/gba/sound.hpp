#ifndef GBAXX_SOUND_HPP
#define GBAXX_SOUND_HPP

#include <gba/int.hpp>

namespace gba {
namespace sound {

struct [[gnu::packed]] stereo_control {
	uint8	volume_right : 3, : 1;
	uint8	volume_left : 3, : 1;
	bool	sound_1_right : 1;
	bool	sound_2_right : 1;
	bool	sound_3_right : 1;
	bool	sound_4_right : 1;
	bool	sound_1_left : 1;
	bool	sound_2_left : 1;
	bool	sound_3_left : 1;
	bool	sound_4_left : 1;
};

struct [[gnu::packed]] mix_control {
	uint8	gb_sound_ratio : 2; // TODO : Make this enum
	bool	full_volume_dma_sound_A : 1;
	bool	full_volume_dma_sound_B : 1;
	uint8	: 4;
	// TODO : Revise
	bool	dma_sound_A_right : 1;
	bool	dma_sound_A_left : 1;
	bool	dma_sound_A_timer : 1;
	bool	dma_sound_A_reset : 1;

	bool	dma_sound_B_right : 1;
	bool	dma_sound_B_left : 1;
	bool	dma_sound_B_timer : 1;
	bool	dma_sound_B_reset : 1;
};

struct [[gnu::packed]] master_control {
	bool	sound_1_status : 1;
	bool	sound_2_status : 1;
	bool	sound_3_status : 1;
	bool	sound_4_status : 1;
	uint8	: 3;
	bool	master_enable : 1;
	uint32	: 24;
};

enum sound_direction {
	increasing = 0,
	decreasing = 1
};

struct [[gnu::packed]] sweep {

	uint8			shifts : 3;
	sound_direction	direction : 1;
	uint8			delay : 3;
	uint16			: 9;
};

enum sound_ratio {
	ratio_7_1 = 0,
	ratio_3_1 = 1,
	ratio_1_1 = 2,
	ratio_1_3 = 3
};

struct [[gnu::packed]] duty {
	uint8		rate : 6;
	sound_ratio	ratio : 2;
};

struct [[gnu::packed]] envelope {
	uint8			delay : 3;
	sound_direction	direction : 1;
	uint8			initial_value : 4;
};

struct [[gnu::packed]] duty_envelope {
	sound::duty		duty;
	sound::envelope	envelope;
};

enum sound_playback {
	continuous,
	timed
};

struct [[gnu::packed]] frequency {
	uint16			frequency : 11;
	uint8			: 3;
	sound_playback	playback : 1;
	bool			restart : 1;
	uint16			: 16;
};

} // sound
} // gba

#endif // define GBAXX_SOUND_HPP
