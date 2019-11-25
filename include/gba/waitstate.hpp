#ifndef GBAXX_WAITSTATE_HPP
#define GBAXX_WAITSTATE_HPP

#include <gba/int.hpp>

namespace gba {
namespace waitstate {

// TODO : Improve this
enum n_cycles {
	n_4 = 0,
	n_3 = 1,
	n_2 = 2,
	n_8 = 3
};

enum s_cycles {
	s_2 = 0,
	s_1 = 1,
};

struct [[gnu::packed]] control {
	n_cycles	sram_wait : 2;
	n_cycles	game_pak_first_access : 2;
	s_cycles	game_pak_sequential_access : 1;
	n_cycles	game_pak_mirror1_first_access : 2;
	s_cycles	game_pak_mirror1_sequential_access : 1;
	n_cycles	game_pak_mirror2_first_access : 2;
	s_cycles	game_pak_mirror2_sequential_access : 1;
	uint8		phi_output : 2, : 1;
	bool		game_pak_prefetch : 1;
	const bool	game_pak_type : 1;
	uint16 : 16;
};

struct [[gnu::packed]] wram_control {
	bool	disable : 1;
	uint8	m_lo : 3, : 1;
	bool	ewram_enable : 1;
	uint32 : 18;
	uint8	ewram_waitstate : 4;
	uint8	m_hi : 4;
};

} // waitstate
} // gba

#endif // define GBAXX_WAITSTATE_HPP