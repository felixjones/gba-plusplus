#ifndef GBAXX_TIMER_HPP
#define GBAXX_TIMER_HPP

#include <cstring>

#include <gba/int.hpp>
#include <gba/io_reg.hpp>

namespace gba {
namespace timer {

enum clock {
	clock_cpu1 = 0x0,
	clock_cpu64 = 0x1,
	clock_cpu256 = 0x2,
	clock_cpu1024 = 0x3,
	clock_cascade = 0x4
};

struct [[gnu::packed]] control {

	clock	tick_rate : 3;
	uint8	: 3;
	bool	emit_irq_overflow : 1;
	bool	enabled : 1;
	uint8	: 8;

};

} // timer

namespace io {

class timer {
public:
	timer& counter( uint16 value ) {
		m_counter.write( value );
		return *this;
	}

	const reg<uint16>& counter() const {
		return m_counter;
	}

	timer& control( const gba::timer::control& value ) {
		m_control.write( value );
		return *this;
	}

	const reg<uint16>& control() const {
		return m_counter;
	}

private:
	reg<uint16>					m_counter;
	reg<gba::timer::control>	m_control;

};

static timer& timer0 = *reinterpret_cast<timer *>( 0x4000100 );
static timer& timer1 = *reinterpret_cast<timer *>( 0x4000104 );
static timer& timer2 = *reinterpret_cast<timer *>( 0x4000108 );
static timer& timer3 = *reinterpret_cast<timer *>( 0x400010C );

} // io
} // gba

#endif // define GBAXX_TIMER_HPP
