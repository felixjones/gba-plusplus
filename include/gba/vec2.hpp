#ifndef GBAXX_VEC2_HPP
#define GBAXX_VEC2_HPP

#include <cassert>

#include <gba/int.hpp>
#include <gba/math.hpp>

namespace gba {

template <typename Type>
struct vec2 {
	using value_type = Type;
	using size_type = uint32;

	using type = vec2<Type>;

	value_type	x;
	value_type	y;

	constexpr vec2() noexcept : x {}, y {} {}

	template <typename OType>
	constexpr vec2( OType scalar ) noexcept : x( scalar ), y( scalar ) {}

	template <typename A, typename B>
	constexpr vec2( A ix, B iy ) noexcept : x( ix ), y( iy ) {}

	template <typename OType>
	constexpr vec2( const vec2<OType>& other ) noexcept : x( other.x ), y( other.y ) {}

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

namespace math {

template <typename A, typename B>
constexpr auto dot( const vec2<A>& a, const vec2<B>& b ) noexcept {
	const auto c = a * b;
	return c.x + c.y;
}

template <typename V>
constexpr auto length( const vec2<V>& v ) noexcept {
	return sqrt( dot( v, v ) );
}

template <typename A, typename B>
constexpr auto distance( const vec2<A>& p0, const vec2<B>& p1 ) noexcept {
	return length( p1 - p0 );
}

template <typename V>
constexpr auto normalize( const vec2<V>& v ) noexcept {
	return v / length( v );
}

} // math

} // gba

#endif // define GBAXX_VEC2_HPP
