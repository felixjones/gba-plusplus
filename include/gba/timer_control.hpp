#ifndef GBAXX_TIMER_CONTROL_HPP
#define GBAXX_TIMER_CONTROL_HPP

#include <gba/fixed_point.hpp>
#include <gba/int.hpp>

namespace gba {

enum timer_cycles {
	cycles_1,
	cycles_64,
	cycles_256,
	cycles_1024
};

struct timer_control {
	timer_cycles	cycles : 2;
	bool			cascading : 1;
	uint8			: 3;
	bool			emit_irq : 1,
					enabled : 1;
	uint8			: 8;
};

} // gba

#endif // define GBAXX_TIMER_CONTROL_HPP
