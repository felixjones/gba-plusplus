#ifndef GBAXX_DMA_CONTROL_HPP
#define GBAXX_DMA_CONTROL_HPP

#include <gba/int.hpp>

namespace gba {
namespace dma {

enum address_function {
	address_increment = 0,
	address_decrement,
	address_constant,
	address_increment_and_reset
};

enum start_timing {
	start_immediate = 0,
	start_vblank,
	start_hblank,
	start_special
};

} // dma

struct dma_control {
	uint8	: 5;

	dma::address_function	address_function_destination : 2,
							address_function_source : 2;

	bool	reset_count : 1,
			transfer_words : 1,
			data_request_from_game_pak : 1;

	dma::start_timing	start_timing : 2;

	bool	irq_on_complete : 1,
			enable_transfer : 1;
};

} // gba

#endif // define GBAXX_DMA_CONTROL_HPP
