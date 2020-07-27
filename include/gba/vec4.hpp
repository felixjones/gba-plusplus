#ifndef GBAXX_VEC4_HPP
#define GBAXX_VEC4_HPP

#include <gba/bios.hpp>
#include <gba/int.hpp>
#include <gba/math.hpp>

namespace gba {

template <typename Type>
struct vec4 {
	using value_type = Type;
	using size_type = uint32;

	using type = vec4<Type>;

	value_type	x;
	value_type	y;
	value_type	z;
	value_type	w;

	constexpr vec4() noexcept : x( 0 ), y( 0 ), z( 0 ), w( 0 ) {}

	template <typename OType>
	constexpr vec4( OType scalar ) noexcept : x( static_cast<value_type>( scalar ) ), y( static_cast<value_type>( scalar ) ), z( static_cast<value_type>( scalar ) ), w( static_cast<value_type>( scalar ) ) {}

	template <typename A, typename B, typename C, typename D>
	constexpr vec4( A ix, B iy, C iz, D iw ) noexcept : x( static_cast<value_type>( ix ) ), y( static_cast<value_type>( iy ) ), z( static_cast<value_type>( iz ) ), w( static_cast<value_type>( iw ) ) {}

	template <typename OType>
	constexpr vec4( const vec4<OType>& other ) noexcept : x( static_cast<value_type>( other.x ) ), y( static_cast<value_type>( other.y ) ), z( static_cast<value_type>( other.z ) ), w( static_cast<value_type>( other.w ) ) {}

	constexpr auto& operator []( size_type i ) noexcept {
		switch ( i ) {
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		}
	}

	constexpr const auto& operator []( size_type i ) const noexcept {
		switch ( i ) {
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		}
	}

	template <typename OType>
	constexpr auto& operator =( const vec4<OType>& other ) noexcept {
		x = static_cast<value_type>( other.x );
		y = static_cast<value_type>( other.y );
		z = static_cast<value_type>( other.z );
		w = static_cast<value_type>( other.w );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const OType& scalar ) noexcept {
		x += static_cast<value_type>( scalar );
		y += static_cast<value_type>( scalar );
		z += static_cast<value_type>( scalar );
		w += static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const vec4<OType>& other ) noexcept {
		x += static_cast<value_type>( other.x );
		y += static_cast<value_type>( other.y );
		z += static_cast<value_type>( other.z );
		w += static_cast<value_type>( other.w );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const OType& scalar ) noexcept {
		x -= static_cast<value_type>( scalar );
		y -= static_cast<value_type>( scalar );
		z -= static_cast<value_type>( scalar );
		w -= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const vec4<OType>& other ) noexcept {
		x -= static_cast<value_type>( other.x );
		y -= static_cast<value_type>( other.y );
		z -= static_cast<value_type>( other.z );
		w -= static_cast<value_type>( other.w );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( const OType& scalar ) noexcept {
		x *= static_cast<value_type>( scalar );
		y *= static_cast<value_type>( scalar );
		z *= static_cast<value_type>( scalar );
		w *= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( const vec4<OType>& other ) noexcept {
		x *= static_cast<value_type>( other.x );
		y *= static_cast<value_type>( other.y );
		z *= static_cast<value_type>( other.z );
		w *= static_cast<value_type>( other.w );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( const OType& scalar ) noexcept {
		x /= static_cast<value_type>( scalar );
		y /= static_cast<value_type>( scalar );
		z /= static_cast<value_type>( scalar );
		w /= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( const vec4<OType>& other ) noexcept {
		x /= static_cast<value_type>( other.x );
		y /= static_cast<value_type>( other.y );
		z /= static_cast<value_type>( other.z );
		w /= static_cast<value_type>( other.w );
		return *this;
	}

	constexpr auto& operator ++() noexcept {
		++x;
		++y;
		++z;
		++w;
		return *this;
	}

	constexpr auto& operator --() noexcept {
		--x;
		--y;
		--z;
		--w;
		return *this;
	}

	constexpr auto& operator ++( int ) noexcept {
		const auto r = *this;
		++x;
		++y;
		++z;
		++w;
		return r;
	}

	constexpr auto& operator --( int ) noexcept {
		const auto r = *this;
		--x;
		--y;
		--z;
		--w;
		return r;
	}

	template <typename OType>
	constexpr auto& operator %=( const OType& scalar ) noexcept {
		x %= static_cast<value_type>( scalar );
		y %= static_cast<value_type>( scalar );
		z %= static_cast<value_type>( scalar );
		w %= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator %=( const vec4<OType>& other ) noexcept {
		x %= static_cast<value_type>( other.x );
		y %= static_cast<value_type>( other.y );
		z %= static_cast<value_type>( other.z );
		w %= static_cast<value_type>( other.w );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator &=( const OType& scalar ) noexcept {
		x &= static_cast<value_type>( scalar );
		y &= static_cast<value_type>( scalar );
		z &= static_cast<value_type>( scalar );
		w &= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator &=( const vec4<OType>& other ) noexcept {
		x &= static_cast<value_type>( other.x );
		y &= static_cast<value_type>( other.y );
		z &= static_cast<value_type>( other.z );
		w &= static_cast<value_type>( other.w );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator |=( const OType& scalar ) noexcept {
		x |= static_cast<value_type>( scalar );
		y |= static_cast<value_type>( scalar );
		z |= static_cast<value_type>( scalar );
		w |= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator |=( const vec4<OType>& other ) noexcept {
		x |= static_cast<value_type>( other.x );
		y |= static_cast<value_type>( other.y );
		z |= static_cast<value_type>( other.z );
		w |= static_cast<value_type>( other.w );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator ^=( const OType& scalar ) noexcept {
		x ^= static_cast<value_type>( scalar );
		y ^= static_cast<value_type>( scalar );
		z ^= static_cast<value_type>( scalar );
		w ^= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator ^=( const vec4<OType>& other ) noexcept {
		x ^= static_cast<value_type>( other.x );
		y ^= static_cast<value_type>( other.y );
		z ^= static_cast<value_type>( other.z );
		w ^= static_cast<value_type>( other.w );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator <<=( const OType& scalar ) noexcept {
		x <<= static_cast<value_type>( scalar );
		y <<= static_cast<value_type>( scalar );
		z <<= static_cast<value_type>( scalar );
		w <<= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator <<=( const vec4<OType>& other ) noexcept {
		x <<= static_cast<value_type>( other.x );
		y <<= static_cast<value_type>( other.y );
		z <<= static_cast<value_type>( other.z );
		w <<= static_cast<value_type>( other.w );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator >>=( const OType& scalar ) noexcept {
		x >>= static_cast<value_type>( scalar );
		y >>= static_cast<value_type>( scalar );
		z >>= static_cast<value_type>( scalar );
		w >>= static_cast<value_type>( scalar );
		return *this;
	}

	template <typename OType>
	constexpr auto& operator >>=( const vec4<OType>& other ) noexcept {
		x >>= static_cast<value_type>( other.x );
		y >>= static_cast<value_type>( other.y );
		z >>= static_cast<value_type>( other.z );
		w >>= static_cast<value_type>( other.w );
		return *this;
	}
};

template <typename Type>
constexpr const auto& operator +( const vec4<Type>& v ) noexcept {
	return v;
}

template <typename Type>
constexpr auto operator -( const vec4<Type>& v ) noexcept {
	return vec4<Type>( -v.x, -v.y, -v.z, -v.w );
}

template <typename A, typename B>
constexpr auto operator +( const vec4<A>& v, B scalar ) noexcept {
	return vec4<A>( v.x + scalar, v.y + scalar, v.z + scalar, v.w + scalar );
}

template <typename A, typename B>
constexpr auto operator +( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<A>( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w );
}

template <typename A, typename B>
constexpr auto operator -( const vec4<A>& v, B scalar ) noexcept {
	return vec4<A>( v.x - scalar, v.y - scalar, v.z - scalar, v.w - scalar );
}

template <typename A, typename B>
constexpr auto operator -( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<A>( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w );
}

template <typename A, typename B>
constexpr auto operator *( const vec4<A>& v, B scalar ) noexcept {
	return vec4<A>( v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar );
}

template <typename A, typename B>
constexpr auto operator *( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<A>( a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w );
}

template <typename A, typename B>
constexpr auto operator /( const vec4<A>& v, B scalar ) noexcept {
	return vec4<A>( v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar );
}

template <typename A, typename B>
constexpr auto operator /( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<A>( a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w );
}

template <typename A, typename B>
constexpr auto operator %( const vec4<A>& v, B scalar ) noexcept {
	return vec4<A>( v.x % scalar, v.y % scalar, v.z % scalar, v.w % scalar );
}

template <typename A, typename B>
constexpr auto operator %( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<A>( a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w );
}

template <typename A, typename B>
constexpr auto operator &( const vec4<A>& v, B scalar ) noexcept {
	return vec4<A>( v.x & scalar, v.y & scalar, v.z & scalar, v.w & scalar );
}

template <typename A, typename B>
constexpr auto operator &( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<A>( a.x & b.x, a.y & b.y, a.z & b.z, a.w & b.w );
}

template <typename A, typename B>
constexpr auto operator |( const vec4<A>& v, B scalar ) noexcept {
	return vec4<A>( v.x | scalar, v.y | scalar, v.z | scalar, v.w | scalar );
}

template <typename A, typename B>
constexpr auto operator |( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<A>( a.x | b.x, a.y | b.y, a.z | b.z, a.w | b.w );
}

template <typename A, typename B>
constexpr auto operator ^( const vec4<A>& v, B scalar ) noexcept {
	return vec4<A>( v.x ^ scalar, v.y ^ scalar, v.z ^ scalar, v.w ^ scalar );
}

template <typename A, typename B>
constexpr auto operator ^( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<A>( a.x ^ b.x, a.y ^ b.y, a.z ^ b.z, a.w ^ b.w );
}

template <typename A, typename B>
constexpr auto operator <<( const vec4<A>& v, B scalar ) noexcept {
	return vec4<A>( v.x << scalar, v.y << scalar, v.z << scalar, v.w << scalar );
}

template <typename A, typename B>
constexpr auto operator <<( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<A>( a.x << b.x, a.y << b.y, a.z << b.z, a.w << b.w );
}

template <typename A, typename B>
constexpr auto operator >>( const vec4<A>& v, B scalar ) noexcept {
	return vec4<A>( v.x >> scalar, v.y >> scalar, v.z >> scalar, v.w >> scalar );
}

template <typename A, typename B>
constexpr auto operator >>( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<A>( a.x >> b.x, a.y >> b.y, a.z >> b.z, a.w >> b.w );
}

template <typename Type>
constexpr auto operator ~( const vec4<Type>& v ) noexcept {
	return vec4<Type>( ~v.x, ~v.y, ~v.z, ~v.w );
}

template <typename A, typename B>
constexpr auto operator ==( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

template <typename A, typename B>
constexpr auto operator !=( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return !( a == b );
}

template <typename A, typename B>
constexpr auto operator &&( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<bool>( a.x && b.x, a.y && b.y, a.z && b.z, a.w && b.w );
}

template <typename A, typename B>
constexpr auto operator ||( const vec4<A>& a, const vec4<B>& b ) noexcept {
	return vec4<bool>( a.x || b.x, a.y || b.y, a.z || b.z, a.w || b.w );
}

namespace math {

template <typename A, typename B>
constexpr auto dot( const vec4<A>& a, const vec4<B>& b ) noexcept {
	const auto c = a * b;
	return c.x + c.y + c.z + c.w;
}

template <typename V>
constexpr auto length( const vec4<V>& v ) noexcept {
	const auto d = dot( v, v );
	if ( __builtin_constant_p( v ) ) {
		return math::sqrt( d );
	} else {
		return bios::sqrt( d );
	}
}

template <typename A, typename B>
constexpr auto distance( const vec4<A>& p0, const vec4<B>& p1 ) noexcept {
	return length( p1 - p0 );
}

template <typename V>
constexpr auto normalize( const vec4<V>& v ) noexcept {
	return v / length( v );
}

} // math

} // gba

#endif // define GBAXX_VEC4_HPP
