#ifndef GBAXX_VEC3_HPP
#define GBAXX_VEC3_HPP

#include <cassert>

#include <gba/int.hpp>
#include <gba/math.hpp>

namespace gba {

template <typename Type>
struct vec3 {
	using value_type = Type;
	using size_type = uint32;

	using type = vec3<Type>;

	value_type	x;
	value_type	y;
	value_type	z;

	constexpr vec3() noexcept : x( 0 ), y( 0 ), z( 0 ) {}

	template <typename OType>
	constexpr vec3( OType scalar ) noexcept : x( static_cast<value_type>( scalar ) ), y( static_cast<value_type>( scalar ) ), z( static_cast<value_type>( scalar ) ) {}

	template <typename A, typename B, typename C>
	constexpr vec3( A ix, B iy, C iz ) noexcept : x( static_cast<value_type>( ix ) ), y( static_cast<value_type>( iy ) ), z( static_cast<value_type>( iz ) ) {}

	template <typename OType>
	constexpr vec3( const vec3<OType>& other ) noexcept : x( static_cast<value_type>( other.x ) ), y( static_cast<value_type>( other.y ) ), z( static_cast<value_type>( other.z ) ) {}

	constexpr auto& operator []( size_type i ) noexcept {
		assert( i >= 0 && i < 3 );

		switch ( i ) {
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}

	constexpr const auto& operator []( size_type i ) const noexcept {
		assert( i >= 0 && i < 3 );

		switch ( i ) {
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}

	template <typename OType>
	constexpr auto& operator =( const vec3<OType>& other ) noexcept {
		x = static_cast<value_type>( other.x );
		y = static_cast<value_type>( other.y );
		z = static_cast<value_type>( other.z );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const OType& scalar ) noexcept {
		x += static_cast<value_type>( scalar );
		y += static_cast<value_type>( scalar );
		z += static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const vec3<OType>& other ) noexcept {
		x += static_cast<value_type>( other.x );
		y += static_cast<value_type>( other.y );
		z += static_cast<value_type>( other.z );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const OType& scalar ) noexcept {
		x -= static_cast<value_type>( scalar );
		y -= static_cast<value_type>( scalar );
		z -= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const vec3<OType>& other ) noexcept {
		x -= static_cast<value_type>( other.x );
		y -= static_cast<value_type>( other.y );
		z -= static_cast<value_type>( other.z );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( const OType& scalar ) noexcept {
		x *= static_cast<value_type>( scalar );
		y *= static_cast<value_type>( scalar );
		z *= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( const vec3<OType>& other ) noexcept {
		x *= static_cast<value_type>( other.x );
		y *= static_cast<value_type>( other.y );
		z *= static_cast<value_type>( other.z );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( const OType& scalar ) noexcept {
		x /= static_cast<value_type>( scalar );
		y /= static_cast<value_type>( scalar );
		z /= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( const vec3<OType>& other ) noexcept {
		x /= static_cast<value_type>( other.x );
		y /= static_cast<value_type>( other.y );
		z /= static_cast<value_type>( other.z);
		return *this;
	}

	constexpr auto& operator ++() noexcept {
		++x;
		++y;
		++z;
		return *this;
	}

	constexpr auto& operator --() noexcept {
		--x;
		--y;
		--z;
		return *this;
	}

	constexpr auto& operator ++( int ) noexcept {
		const auto r = *this;
		++x;
		++y;
		++z;
		return r;
	}

	constexpr auto& operator --( int ) noexcept {
		const auto r = *this;
		--x;
		--y;
		--z;
		return r;
	}

	template <typename OType>
	constexpr auto& operator %=( const OType& scalar ) noexcept {
		x %= static_cast<value_type>( scalar );
		y %= static_cast<value_type>( scalar );
		z %= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator %=( const vec3<OType>& other ) noexcept {
		x %= static_cast<value_type>( other.x );
		y %= static_cast<value_type>( other.y );
		z %= static_cast<value_type>( other.z );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator &=( const OType& scalar ) noexcept {
		x &= static_cast<value_type>( scalar );
		y &= static_cast<value_type>( scalar );
		z &= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator &=( const vec3<OType>& other ) noexcept {
		x &= static_cast<value_type>( other.x );
		y &= static_cast<value_type>( other.y );
		z &= static_cast<value_type>( other.z );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator |=( const OType& scalar ) noexcept {
		x |= static_cast<value_type>( scalar );
		y |= static_cast<value_type>( scalar );
		z |= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator |=( const vec3<OType>& other ) noexcept {
		x |= static_cast<value_type>( other.x );
		y |= static_cast<value_type>( other.y );
		z |= static_cast<value_type>( other.z );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator ^=( const OType& scalar ) noexcept {
		x ^= static_cast<value_type>( scalar );
		y ^= static_cast<value_type>( scalar );
		z ^= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator ^=( const vec3<OType>& other ) noexcept {
		x ^= static_cast<value_type>( other.x );
		y ^= static_cast<value_type>( other.y );
		z ^= static_cast<value_type>( other.z );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator <<=( const OType& scalar ) noexcept {
		x <<= static_cast<value_type>( scalar );
		y <<= static_cast<value_type>( scalar );
		z <<= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator <<=( const vec3<OType>& other ) noexcept {
		x <<= static_cast<value_type>( other.x );
		y <<= static_cast<value_type>( other.y );
		z <<= static_cast<value_type>( other.z );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator >>=( const OType& scalar ) noexcept {
		x >>= static_cast<value_type>( scalar );
		y >>= static_cast<value_type>( scalar );
		z >>= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator >>=( const vec3<OType>& other ) noexcept {
		x >>= static_cast<value_type>( other.x );
		y >>= static_cast<value_type>( other.y );
		z >>= static_cast<value_type>( other.z );
		return *this;
	}
};

template <typename Type>
constexpr const auto& operator +( const vec3<Type>& v ) noexcept {
	return v;
}

template <typename Type>
constexpr auto operator -( const vec3<Type>& v ) noexcept {
	return vec3<Type>( -v.x, -v.y, -v.z );
}

template <typename A, typename B>
constexpr auto operator +( const vec3<A>& v, B scalar ) noexcept {
	return vec3<A>( v.x + scalar, v.y + scalar, v.z + scalar );
}

template <typename A, typename B>
constexpr auto operator +( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<A>( a.x + b.x, a.y + b.y, a.z + b.z );
}

template <typename A, typename B>
constexpr auto operator -( const vec3<A>& v, B scalar ) noexcept {
	return vec3<A>( v.x - scalar, v.y - scalar, v.z - scalar );
}

template <typename A, typename B>
constexpr auto operator -( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<A>( a.x - b.x, a.y - b.y, a.z - b.z );
}

template <typename A, typename B>
constexpr auto operator *( const vec3<A>& v, B scalar ) noexcept {
	return vec3<A>( v.x * scalar, v.y * scalar, v.z * scalar );
}

template <typename A, typename B>
constexpr auto operator *( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<A>( a.x * b.x, a.y * b.y, a.z * b.z );
}

template <typename A, typename B>
constexpr auto operator /( const vec3<A>& v, B scalar ) noexcept {
	return vec3<A>( v.x / scalar, v.y / scalar, v.z / scalar );
}

template <typename A, typename B>
constexpr auto operator /( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<A>( a.x / b.x, a.y / b.y, a.z / b.z );
}

template <typename A, typename B>
constexpr auto operator %( const vec3<A>& v, B scalar ) noexcept {
	return vec3<A>( v.x % scalar, v.y % scalar, v.z % scalar );
}

template <typename A, typename B>
constexpr auto operator %( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<A>( a.x % b.x, a.y % b.y, a.z % b.z );
}

template <typename A, typename B>
constexpr auto operator &( const vec3<A>& v, B scalar ) noexcept {
	return vec3<A>( v.x & scalar, v.y & scalar, v.z & scalar );
}

template <typename A, typename B>
constexpr auto operator &( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<A>( a.x & b.x, a.y & b.y, a.z & b.z );
}

template <typename A, typename B>
constexpr auto operator |( const vec3<A>& v, B scalar ) noexcept {
	return vec3<A>( v.x | scalar, v.y | scalar, v.z | scalar );
}

template <typename A, typename B>
constexpr auto operator |( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<A>( a.x | b.x, a.y | b.y, a.z | b.z );
}

template <typename A, typename B>
constexpr auto operator ^( const vec3<A>& v, B scalar ) noexcept {
	return vec3<A>( v.x ^ scalar, v.y ^ scalar, v.z ^ scalar );
}

template <typename A, typename B>
constexpr auto operator ^( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<A>( a.x ^ b.x, a.y ^ b.y, a.z ^ b.z );
}

template <typename A, typename B>
constexpr auto operator <<( const vec3<A>& v, B scalar ) noexcept {
	return vec3<A>( v.x << scalar, v.y << scalar, v.z << scalar );
}

template <typename A, typename B>
constexpr auto operator <<( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<A>( a.x << b.x, a.y << b.y, a.z << b.z );
}

template <typename A, typename B>
constexpr auto operator >>( const vec3<A>& v, B scalar ) noexcept {
	return vec3<A>( v.x >> scalar, v.y >> scalar, v.z >> scalar );
}

template <typename A, typename B>
constexpr auto operator >>( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<A>( a.x >> b.x, a.y >> b.y, a.z >> b.z );
}

template <typename Type>
constexpr auto operator ~( const vec3<Type>& v ) noexcept {
	return vec3<Type>( ~v.x, ~v.y, ~v.z );
}

template <typename A, typename B>
constexpr auto operator ==( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

template <typename A, typename B>
constexpr auto operator !=( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return !( a == b );
}

template <typename A, typename B>
constexpr auto operator &&( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<bool>( a.x && b.x, a.y && b.y, a.z && b.z );
}

template <typename A, typename B>
constexpr auto operator ||( const vec3<A>& a, const vec3<B>& b ) noexcept {
	return vec3<bool>( a.x || b.x, a.y || b.y, a.z || b.z );
}

namespace math {

template <typename A, typename B>
constexpr auto dot( const vec3<A>& a, const vec3<B>& b ) noexcept {
	const auto c = a * b;
	return c.x + c.y + c.z;
}

template <typename A, typename B>
constexpr auto cross( const vec3<A>& x, const vec3<B>& y ) noexcept {
	return vec3<A>( 
		x.y * y.z - x.z * y.y,
		x.z * y.x - x.x * y.z, 
		x.x * y.y - x.y * y.x );
}

template <typename V>
constexpr auto length( const vec3<V>& v ) noexcept {
	return sqrt( dot( v, v ) );
}

template <typename A, typename B>
constexpr auto distance( const vec3<A>& p0, const vec3<B>& p1 ) noexcept {
	return length( p1 - p0 );
}

template <typename V>
constexpr auto normalize( const vec3<V>& v ) noexcept {
	return v / length( v );
}

} // math

} // gba

#endif // define GBAXX_VEC3_HPP
