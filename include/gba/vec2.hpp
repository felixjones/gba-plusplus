#ifndef GBAXX_VEC2_HPP
#define GBAXX_VEC2_HPP

#include <cassert>

#include <gba/int.hpp>

namespace gba {

template <typename Type>
struct vec2 {
	using value_type = Type;
	using size_type = uint32;

	using type = vec2<Type>;

	value_type	x;
	value_type	y;

	constexpr vec2() noexcept : x( 0 ), y( 0 ) {}

	template <typename OType>
	constexpr vec2( OType scalar ) noexcept : x( static_cast<value_type>( scalar ) ), y( static_cast<value_type>( scalar ) ) {}

	template <typename A, typename B>
	constexpr vec2( A ix, B iy ) noexcept : x( static_cast<value_type>( ix ) ), y( static_cast<value_type>( iy ) ) {}

	template <typename OType>
	constexpr vec2( const vec2<OType>& other ) noexcept : x( static_cast<value_type>( other.x ) ), y( static_cast<value_type>( other.y ) ) {}

	constexpr auto& operator []( size_type i ) noexcept {
		assert( i >= 0 && i < 2 );

		switch ( i ) {
		default:
		case 0:
			return x;
		case 1:
			return y;
		}
	}

	constexpr const auto& operator []( size_type i ) const noexcept {
		assert( i >= 0 && i < 2 );

		switch ( i ) {
		default:
		case 0:
			return x;
		case 1:
			return y;
		}
	}

	template <typename OType>
	constexpr auto& operator =( const vec2<OType>& other ) noexcept {
		x = static_cast<value_type>( other.x );
		y = static_cast<value_type>( other.y );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const OType& scalar ) noexcept {
		x += static_cast<value_type>( scalar );
		y += static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const vec2<OType>& other ) noexcept {
		x += static_cast<value_type>( other.x );
		y += static_cast<value_type>( other.y );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const OType& scalar ) noexcept {
		x -= static_cast<value_type>( scalar );
		y -= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const vec2<OType>& other ) noexcept {
		x -= static_cast<value_type>( other.x );
		y -= static_cast<value_type>( other.y );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( const OType& scalar ) noexcept {
		x *= static_cast<value_type>( scalar );
		y *= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( const vec2<OType>& other ) noexcept {
		x *= static_cast<value_type>( other.x );
		y *= static_cast<value_type>( other.y );
		return *this;
	}
	
	template <typename OType>
	constexpr auto& operator /=( const OType& scalar ) noexcept {
		x /= static_cast<value_type>( scalar );
		y /= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( const vec2<OType>& other ) noexcept {
		x /= static_cast<value_type>( other.x );
		y /= static_cast<value_type>( other.y );
		return *this;
	}

	constexpr auto& operator ++() noexcept {
		++x;
		++y;
		return *this;
	}

	constexpr auto& operator --() noexcept {
		--x;
		--y;
		return *this;
	}

	constexpr auto& operator ++( int ) noexcept {
		const auto r = *this;
		++x;
		++y;
		return r;
	}

	constexpr auto& operator --( int ) noexcept {
		const auto r = *this;
		--x;
		--y;
		return r;
	}

	template <typename OType>
	constexpr auto& operator %=( const OType& scalar ) noexcept {
		x %= static_cast<value_type>( scalar );
		y %= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator %=( const vec2<OType>& other ) noexcept {
		x %= static_cast<value_type>( other.x );
		y %= static_cast<value_type>( other.y );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator &=( const OType& scalar ) noexcept {
		x &= static_cast<value_type>( scalar );
		y &= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator &=( const vec2<OType>& other ) noexcept {
		x &= static_cast<value_type>( other.x );
		y &= static_cast<value_type>( other.y );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator |=( const OType& scalar ) noexcept {
		x |= static_cast<value_type>( scalar );
		y |= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator |=( const vec2<OType>& other ) noexcept {
		x |= static_cast<value_type>( other.x );
		y |= static_cast<value_type>( other.y );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator ^=( const OType& scalar ) noexcept {
		x ^= static_cast<value_type>( scalar );
		y ^= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator ^=( const vec2<OType>& other ) noexcept {
		x ^= static_cast<value_type>( other.x );
		y ^= static_cast<value_type>( other.y );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator <<=( const OType& scalar ) noexcept {
		x <<= static_cast<value_type>( scalar );
		y <<= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator <<=( const vec2<OType>& other ) noexcept {
		x <<= static_cast<value_type>( other.x );
		y <<= static_cast<value_type>( other.y );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator >>=( const OType& scalar ) noexcept {
		x >>= static_cast<value_type>( scalar );
		y >>= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator >>=( const vec2<OType>& other ) noexcept {
		x >>= static_cast<value_type>( other.x );
		y >>= static_cast<value_type>( other.y );
		return *this;
	}
};

template <typename Type>
constexpr const auto& operator +( const vec2<Type>& v ) noexcept {
	return v;
}

template <typename Type>
constexpr auto operator -( const vec2<Type>& v ) noexcept {
	return vec2<Type>( -v.x, -v.y );
}

template <typename A, typename B>
constexpr auto operator +( const vec2<A>& v, B scalar ) noexcept {
	return vec2<A>( v.x + scalar, v.y + scalar );
}

template <typename A, typename B>
constexpr auto operator +( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<A>( a.x + b.x, a.y + b.y );
}

template <typename A, typename B>
constexpr auto operator -( const vec2<A>& v, B scalar ) noexcept {
	return vec2<A>( v.x - scalar, v.y - scalar );
}

template <typename A, typename B>
constexpr auto operator -( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<A>( a.x - b.x, a.y - b.y );
}

template <typename A, typename B>
constexpr auto operator *( const vec2<A>& v, B scalar ) noexcept {
	return vec2<A>( v.x * scalar, v.y * scalar );
}

template <typename A, typename B>
constexpr auto operator *( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<A>( a.x * b.x, a.y * b.y );
}

template <typename A, typename B>
constexpr auto operator /( const vec2<A>& v, B scalar ) noexcept {
	return vec2<A>( v.x / scalar, v.y / scalar );
}

template <typename A, typename B>
constexpr auto operator /( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<A>( a.x / b.x, a.y / b.y );
}

template <typename A, typename B>
constexpr auto operator %( const vec2<A>& v, B scalar ) noexcept {
	return vec2<A>( v.x % scalar, v.y % scalar );
}

template <typename A, typename B>
constexpr auto operator %( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<A>( a.x % b.x, a.y % b.y );
}

template <typename A, typename B>
constexpr auto operator &( const vec2<A>& v, B scalar ) noexcept {
	return vec2<A>( v.x & scalar, v.y & scalar );
}

template <typename A, typename B>
constexpr auto operator &( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<A>( a.x & b.x, a.y & b.y );
}

template <typename A, typename B>
constexpr auto operator |( const vec2<A>& v, B scalar ) noexcept {
	return vec2<A>( v.x | scalar, v.y | scalar );
}

template <typename A, typename B>
constexpr auto operator |( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<A>( a.x | b.x, a.y | b.y );
}

template <typename A, typename B>
constexpr auto operator ^( const vec2<A>& v, B scalar ) noexcept {
	return vec2<A>( v.x ^ scalar, v.y ^ scalar );
}

template <typename A, typename B>
constexpr auto operator ^( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<A>( a.x ^ b.x, a.y ^ b.y );
}

template <typename A, typename B>
constexpr auto operator <<( const vec2<A>& v, B scalar ) noexcept {
	return vec2<A>( v.x << scalar, v.y << scalar );
}

template <typename A, typename B>
constexpr auto operator <<( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<A>( a.x << b.x, a.y << b.y );
}

template <typename A, typename B>
constexpr auto operator >>( const vec2<A>& v, B scalar ) noexcept {
	return vec2<A>( v.x >> scalar, v.y >> scalar );
}

template <typename A, typename B>
constexpr auto operator >>( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<A>( a.x >> b.x, a.y >> b.y );
}

template <typename Type>
constexpr auto operator ~( const vec2<Type>& v ) noexcept {
	return vec2<Type>( ~v.x, ~v.y );
}

template <typename A, typename B>
constexpr auto operator ==( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return a.x == b.x && a.y == b.y;
}

template <typename A, typename B>
constexpr auto operator !=( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return !( a == b );
}

template <typename A, typename B>
constexpr auto operator &&( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<bool>( a.x && b.x, a.y && b.y );
}

template <typename A, typename B>
constexpr auto operator ||( const vec2<A>& a, const vec2<B>& b ) noexcept {
	return vec2<bool>( a.x || b.x, a.y || b.y );
}

} // gba

#endif // define GBAXX_VEC2_HPP
