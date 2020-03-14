#ifndef GBAXX_WINDOW_HPP
#define GBAXX_WINDOW_HPP

#include <gba/int.hpp>

namespace gba {

struct window_control {
	bool	background0 : 1,
			background1 : 1,
			background2 : 1,
			background3 : 1,
			object		: 1,
			color_blend	: 1,
			: 2;
};

template <typename Type>
struct dim {
	using value_type = Type;
	using size_type = uint32;

	using type = dim<Type>;

	value_type	max;
	value_type	min;

	constexpr dim() noexcept : max( 0 ), min( 0 ) {}

	template <typename A, typename B>
	constexpr dim( A a, B b ) noexcept : max( static_cast<value_type>( a ) ), min( static_cast<value_type>( b ) ) {}

	template <typename OType>
	constexpr dim( const dim<OType>& other ) noexcept : max( static_cast<value_type>( other.max ) ), min( static_cast<value_type>( other.min ) ) {}

	constexpr auto& operator []( size_type i ) noexcept {
		assert( i >= 0 && i < 2 );

		switch ( i ) {
		default:
		case 0:
			return max;
		case 1:
			return min;
		}
	}

	constexpr const auto& operator []( size_type i ) const noexcept {
		assert( i >= 0 && i < 2 );

		switch ( i ) {
		default:
		case 0:
			return max;
		case 1:
			return min;
		}
	}

	template <typename OType>
	constexpr auto& operator =( const dim<OType>& other ) noexcept {
		max = static_cast<value_type>( other.max );
		min = static_cast<value_type>( other.min );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const OType& scalar ) noexcept {
		max += static_cast<value_type>( scalar );
		min += static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const dim<OType>& other ) noexcept {
		max += static_cast<value_type>( other.max );
		min += static_cast<value_type>( other.min );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const OType& scalar ) noexcept {
		max -= static_cast<value_type>( scalar );
		min -= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const dim<OType>& other ) noexcept {
		max -= static_cast<value_type>( other.max );
		min -= static_cast<value_type>( other.min );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( const OType& scalar ) noexcept {
		max *= static_cast<value_type>( scalar );
		min *= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( const dim<OType>& other ) noexcept {
		max *= static_cast<value_type>( other.max );
		min *= static_cast<value_type>( other.min );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( const OType& scalar ) noexcept {
		max /= static_cast<value_type>( scalar );
		min /= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( const dim<OType>& other ) noexcept {
		max /= static_cast<value_type>( other.max );
		min /= static_cast<value_type>( other.min );
		return *this;
	}

	constexpr auto& operator ++() noexcept {
		++max;
		++min;
		return *this;
	}

	constexpr auto& operator --() noexcept {
		--max;
		--min;
		return *this;
	}

	constexpr auto& operator ++( int ) noexcept {
		const auto r = *this;
		++max;
		++min;
		return r;
	}

	constexpr auto& operator --( int ) noexcept {
		const auto r = *this;
		--max;
		--min;
		return r;
	}

	template <typename OType>
	constexpr auto& operator %=( const OType& scalar ) noexcept {
		max %= static_cast<value_type>( scalar );
		min %= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator %=( const dim<OType>& other ) noexcept {
		max %= static_cast<value_type>( other.max );
		min %= static_cast<value_type>( other.min );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator &=( const OType& scalar ) noexcept {
		max &= static_cast<value_type>( scalar );
		min &= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator &=( const dim<OType>& other ) noexcept {
		max &= static_cast<value_type>( other.max );
		min &= static_cast<value_type>( other.min );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator |=( const OType& scalar ) noexcept {
		max |= static_cast<value_type>( scalar );
		min |= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator |=( const dim<OType>& other ) noexcept {
		max |= static_cast<value_type>( other.max );
		min |= static_cast<value_type>( other.min );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator ^=( const OType& scalar ) noexcept {
		max ^= static_cast<value_type>( scalar );
		min ^= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator ^=( const dim<OType>& other ) noexcept {
		max ^= static_cast<value_type>( other.max );
		min ^= static_cast<value_type>( other.min );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator <<=( const OType& scalar ) noexcept {
		max <<= static_cast<value_type>( scalar );
		min <<= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator <<=( const dim<OType>& other ) noexcept {
		max <<= static_cast<value_type>( other.max );
		min <<= static_cast<value_type>( other.min );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator >>=( const OType& scalar ) noexcept {
		max >>= static_cast<value_type>( scalar );
		min >>= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator >>=( const dim<OType>& other ) noexcept {
		max >>= static_cast<value_type>( other.max );
		min >>= static_cast<value_type>( other.min );
		return *this;
	}
};

template <typename Type>
constexpr const auto& operator +( const dim<Type>& v ) noexcept {
	return v;
}

template <typename Type>
constexpr auto operator -( const dim<Type>& v ) noexcept {
	return dim<Type>( -v.max, -v.min );
}

template <typename A, typename B>
constexpr auto operator +( const dim<A>& v, B scalar ) noexcept {
	return dim<A>( v.max + scalar, v.min + scalar );
}

template <typename A, typename B>
constexpr auto operator +( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<A>( a.max + b.max, a.min + b.min );
}

template <typename A, typename B>
constexpr auto operator -( const dim<A>& v, B scalar ) noexcept {
	return dim<A>( v.max - scalar, v.min - scalar );
}

template <typename A, typename B>
constexpr auto operator -( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<A>( a.max - b.max, a.min - b.min );
}

template <typename A, typename B>
constexpr auto operator *( const dim<A>& v, B scalar ) noexcept {
	return dim<A>( v.max * scalar, v.min * scalar );
}

template <typename A, typename B>
constexpr auto operator *( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<A>( a.max * b.max, a.min * b.min );
}

template <typename A, typename B>
constexpr auto operator /( const dim<A>& v, B scalar ) noexcept {
	return dim<A>( v.max / scalar, v.min / scalar );
}

template <typename A, typename B>
constexpr auto operator /( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<A>( a.max / b.max, a.min / b.min );
}

template <typename A, typename B>
constexpr auto operator %( const dim<A>& v, B scalar ) noexcept {
	return dim<A>( v.max % scalar, v.min % scalar );
}

template <typename A, typename B>
constexpr auto operator %( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<A>( a.max % b.max, a.min % b.min );
}

template <typename A, typename B>
constexpr auto operator &( const dim<A>& v, B scalar ) noexcept {
	return dim<A>( v.max & scalar, v.min & scalar );
}

template <typename A, typename B>
constexpr auto operator &( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<A>( a.max & b.max, a.min & b.min );
}

template <typename A, typename B>
constexpr auto operator |( const dim<A>& v, B scalar ) noexcept {
	return dim<A>( v.max | scalar, v.min | scalar );
}

template <typename A, typename B>
constexpr auto operator |( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<A>( a.max | b.max, a.min | b.min );
}

template <typename A, typename B>
constexpr auto operator ^( const dim<A>& v, B scalar ) noexcept {
	return dim<A>( v.max ^ scalar, v.min ^ scalar );
}

template <typename A, typename B>
constexpr auto operator ^( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<A>( a.max ^ b.max, a.min ^ b.min );
}

template <typename A, typename B>
constexpr auto operator <<( const dim<A>& v, B scalar ) noexcept {
	return dim<A>( v.max << scalar, v.min << scalar );
}

template <typename A, typename B>
constexpr auto operator <<( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<A>( a.max << b.max, a.min << b.min );
}

template <typename A, typename B>
constexpr auto operator >>( const dim<A>& v, B scalar ) noexcept {
	return dim<A>( v.max >> scalar, v.min >> scalar );
}

template <typename A, typename B>
constexpr auto operator >>( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<A>( a.max >> b.max, a.min >> b.min );
}

template <typename Type>
constexpr auto operator ~( const dim<Type>& v ) noexcept {
	return dim<Type>( ~v.max, ~v.min );
}

template <typename A, typename B>
constexpr auto operator ==( const dim<A>& a, const dim<B>& b ) noexcept {
	return a.max == b.max && a.min == b.min;
}

template <typename A, typename B>
constexpr auto operator !=( const dim<A>& a, const dim<B>& b ) noexcept {
	return !( a == b );
}

template <typename A, typename B>
constexpr auto operator &&( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<bool>( a.max && b.max, a.min && b.min );
}

template <typename A, typename B>
constexpr auto operator ||( const dim<A>& a, const dim<B>& b ) noexcept {
	return dim<bool>( a.max || b.max, a.min || b.min );
}

} // gba

#endif // define GBAXX_WINDOW_HPP
