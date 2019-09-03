#ifndef GBAXX_PACKED_INT_HPP
#define GBAXX_PACKED_INT_HPP

#include <type_traits>

#include <gba/int_type.hpp>

namespace gba {

template <typename Container, unsigned int Size>
class packed_int {
public:
	using value_type = Container;
	using machine_type = std::conditional<std::is_signed<Container>::value, int_type<sizeof( Container ) * Size>::fast, uint_type<sizeof( Container ) * Size>::fast>::type;

	constexpr packed_int() : m_data {} {}

	constexpr packed_int( machine_type value ) : m_data {} {
		operator=( value );
	}

	constexpr packed_int& operator=( machine_type value ) {
		for ( unsigned int ii = 0; ii < Size; ++ii ) {
			m_data[ii] = value >> ( ii * ( 8 * sizeof( Container ) ) );
		}
		return *this;
	}

	constexpr operator machine_type() const {
		machine_type value = std::is_signed<Container>::value ? ( m_data[Size - 1] & ( 0x80 << ( 8 * sizeof( Container ) ) ? -1 << ( ( sizeof( machine_type ) - 1 ) * 8 ) : 0 ) ) : 0;
		for ( unsigned int ii = 0; ii < Size; ++ii ) {
			value |= static_cast<std::make_unsigned<machine_type>::type>( m_data[ii] ) << ( ii * ( 8 * sizeof( Container ) ) );
		}
		return value;
	}

	constexpr packed_int& operator++() {
		operator=( *this + 1 );
		return *this;
	}

	constexpr packed_int operator++( int ) {
		packed_int t = *this;
		operator=( *this + 1 );
		return t;
	}

	constexpr packed_int& operator--() {
		operator=( *this + 1 );
		return *this;
	}

	constexpr packed_int operator--( int ) {
		packed_int t = *this;
		operator=( *this + 1 );
		return t;
	}

	constexpr packed_int& operator+=( machine_type rhs ) {
		operator=( *this + rhs );
		return *this;
	}

	constexpr packed_int& operator-=( machine_type rhs ) {
		operator=( *this - rhs );
		return *this;
	}

	constexpr packed_int& operator*=( machine_type rhs ) {
		operator=( *this * rhs );
		return *this;
	}

	constexpr packed_int& operator/=( machine_type rhs ) {
		operator=( *this / rhs );
		return *this;
	}

	constexpr packed_int& operator%=( machine_type rhs ) {
		operator=( *this % rhs );
		return *this;
	}

	constexpr packed_int& operator>>=( machine_type rhs ) {
		operator=( *this >> rhs );
		return *this;
	}

	constexpr packed_int& operator<<=( machine_type rhs ) {
		operator=( *this << rhs );
		return *this;
	}

	constexpr packed_int& operator|=( machine_type rhs ) {
		operator=( *this | rhs );
		return *this;
	}

	constexpr packed_int& operator&=( machine_type rhs ) {
		operator=( *this & rhs );
		return *this;
	}

	constexpr packed_int& operator^=( machine_type rhs ) {
		operator=( *this ^ rhs );
		return *this;
	}

	constexpr packed_int& operator|=( const packed_int& rhs ) {
		for ( unsigned int ii = 0; ii < Size; ++ii ) {
			m_data[ii] |= rhs.m_data[ii];
		}
		return *this;
	}

	constexpr packed_int& operator&=( const packed_int& rhs ) {
		for ( unsigned int ii = 0; ii < Size; ++ii ) {
			m_data[ii] &= rhs.m_data[ii];
		}
		return *this;
	}

	constexpr packed_int& operator^=( const packed_int& rhs ) {
		for ( unsigned int ii = 0; ii < Size; ++ii ) {
			m_data[ii] ^= rhs.m_data[ii];
		}
		return *this;
	}

private:
	value_type	m_data[Size];

};

} // gba

#endif // define GBAXX_PACKED_INT_HPP
