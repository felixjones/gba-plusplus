#ifndef GBAXX_BIT_BOOL_HPP
#define GBAXX_BIT_BOOL_HPP

namespace gba {

template <typename Container, unsigned int Shift = 0>
class [[gnu::packed]] bit_bool {
	static_assert( Shift < ( sizeof( Container ) * 8 ), "Shift cannot be outside range of Container" );
public:
	using value_type = Container;

	constexpr bit_bool() {}

	constexpr bit_bool( bool value ) {
		operator=( value );
	}

	constexpr bit_bool& operator=( bool value ) {
		m_data = ( value << Shift );
		return *this;
	}

	constexpr operator bool() const {
		return m_data & ( 1 << Shift );
	}

	constexpr bit_bool& operator+=( bool rhs ) {
		operator=( *this + rhs );
		return *this;
	}

	constexpr bit_bool& operator-=( bool rhs ) {
		operator=( *this - rhs );
		return *this;
	}

	constexpr bit_bool& operator*=( bool rhs ) {
		operator=( *this * rhs );
		return *this;
	}

	constexpr bit_bool& operator/=( bool rhs ) {
		operator=( *this / rhs );
		return *this;
	}

	constexpr bit_bool& operator%=( bool rhs ) {
		operator=( *this % rhs );
		return *this;
	}

	constexpr bit_bool& operator>>=( bool rhs ) {
		operator=( *this >> rhs );
		return *this;
	}

	constexpr bit_bool& operator<<=( bool rhs ) {
		operator=( *this << rhs );
		return *this;
	}

	constexpr bit_bool& operator|=( bool rhs ) {
		operator=( *this | rhs );
		return *this;
	}

	constexpr bit_bool& operator&=( bool rhs ) {
		operator=( *this & rhs );
		return *this;
	}

	constexpr bit_bool& operator^=( bool rhs ) {
		operator=( *this ^ rhs );
		return *this;
	}

private:
	value_type	m_data;

};

} // gba

#endif // define GBAXX_BIT_BOOL_HPP