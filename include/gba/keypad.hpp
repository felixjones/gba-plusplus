#ifndef GBAXX_KEYPAD_HPP
#define GBAXX_KEYPAD_HPP

#include <gba/int_type.hpp>

namespace gba {
namespace keypad {

struct [[gnu::packed]] bits {

	bool	button_a : 1,
			button_b : 1,
			select : 1,
			start : 1,
			dpad_right : 1,
			dpad_left : 1,
			dpad_up : 1,
			dpad_down : 1,
			button_r : 1,
			button_l : 1,
			: 4;

	bool	irq_emit : 1,
			irq_condition_and : 1;

};

class [[gnu::packed]] state {
public:

	constexpr state() : m_data {} {}
	constexpr state( const bits& b ) : m_data( b ) {}
	constexpr state( const state& other ) : m_data( other.m_data ) {}

	template <typename Type = int_sized_type<1>::fast>
	constexpr Type axis_x() const {
		Type axis = 0;
		if ( !m_data.dpad_right ) axis += 1;
		if ( !m_data.dpad_left ) axis -= 1;
		return axis;
	}

	template <typename Type = int_sized_type<1>::fast>
	constexpr Type axis_y() const {
		Type axis = 0;
		if ( !m_data.dpad_up ) axis += 1;
		if ( !m_data.dpad_down ) axis -= 1;
		return axis;
	}

	constexpr bool button_a() const {
		return !m_data.button_a;
	}

	constexpr bool button_b() const {
		return !m_data.button_b;
	}

	constexpr bool select() const {
		return !m_data.select;
	}

	constexpr bool start() const {
		return !m_data.start;
	}

	constexpr bool dpad_right() const {
		return !m_data.dpad_right;
	}

	constexpr bool dpad_left() const {
		return !m_data.dpad_left;
	}

	constexpr bool dpad_up() const {
		return !m_data.dpad_up;
	}

	constexpr bool dpad_down() const {
		return !m_data.dpad_down;
	}

	constexpr bool button_r() const {
		return !m_data.button_r;
	}

	constexpr bool button_l() const {
		return !m_data.button_l;
	}

private:
	bits	m_data;

};

// TODO : Some handy helper stuff

} // keypad
} // gba


#endif // define GBAXX_KEYPAD_HPP