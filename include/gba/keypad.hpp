#ifndef GBAXX_KEYPAD_HPP
#define GBAXX_KEYPAD_HPP

#include <gba/int.hpp>

namespace gba {

struct keys {
	uint16	data;
};

namespace key {

	static constexpr auto Select = ( 0x1 << 2 );
	static constexpr auto Start = ( 0x1 << 3 );

	namespace button {

		static constexpr auto A = ( 0x1 << 0 );
		static constexpr auto B = ( 0x1 << 1 );
		static constexpr auto R = ( 0x1 << 8 );
		static constexpr auto L = ( 0x1 << 9 );

	} // button

	namespace dpad {

		static constexpr auto Right = ( 0x1 << 4 );
		static constexpr auto Left = ( 0x1 << 5 );
		static constexpr auto Up = ( 0x1 << 6 );
		static constexpr auto Down = ( 0x1 << 7 );

	} // dpad

} // key

class key_state {
public:
	constexpr key_state() noexcept : m_bitmask( 0 ) {}

	constexpr key_state( const keys& k ) noexcept : m_bitmask( ~k.data ) {}

	constexpr key_state( const key_state& other ) noexcept : m_bitmask( other.m_bitmask ) {}

	template <typename Type = int_sized_type<1>::fast>
	constexpr Type axis_x() const noexcept {
		Type axis = 0;
		if ( m_bitmask & key::dpad::Right ) axis += 1;
		if ( m_bitmask & key::dpad::Left ) axis -= 1;
		return axis;
	}

	template <typename Type = int_sized_type<1>::fast>
	constexpr Type axis_y() const noexcept {
		Type axis = 0;
		if ( m_bitmask & key::dpad::Up ) axis += 1;
		if ( m_bitmask & key::dpad::Down ) axis -= 1;
		return axis;
	}

	constexpr bool button_a() const noexcept {
		return m_bitmask & key::button::A;
	}

	constexpr bool button_b() const noexcept {
		return m_bitmask & key::button::B;
	}

	constexpr bool select() const noexcept {
		return m_bitmask & key::Select;
	}

	constexpr bool start() const noexcept {
		return m_bitmask & key::Start;
	}

	constexpr bool dpad_right() const noexcept {
		return m_bitmask & key::dpad::Right;
	}

	constexpr bool dpad_left() const noexcept {
		return m_bitmask & key::dpad::Left;
	}

	constexpr bool dpad_up() const noexcept {
		return m_bitmask & key::dpad::Up;
	}

	constexpr bool dpad_down() const noexcept {
		return m_bitmask & key::dpad::Down;
	}

	constexpr bool button_r() const noexcept {
		return m_bitmask & key::button::R;
	}

	constexpr bool button_l() const noexcept {
		return m_bitmask & key::button::L;
	}

private:
	uint16	m_bitmask;

};

} // gba

#endif // GBAXX_KEYPAD_HPP