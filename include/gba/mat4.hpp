#ifndef GBAXX_MAT4_HPP
#define GBAXX_MAT4_HPP

#include <cassert>

#include <gba/int.hpp>
#include <gba/math.hpp>
#include <gba/vec3.hpp>
#include <gba/vec4.hpp>

namespace gba {

template <typename Type>
struct mat4 {
	template <typename L, typename R, typename B, typename T>
	static constexpr auto ortho( L left, R right, B bottom, T top ) {
		return mat4(
			static_cast<value_type>( 2 ) / ( right - left ), 0, 0, 0,
			0, static_cast<value_type>( 2 ) / ( top - bottom ), 0, 0,
			0, 0, -static_cast<value_type>( 1 ), 0,
			-static_cast<value_type>( ( right + left ) / ( right - left ) ), -static_cast<value_type>( ( top + bottom ) / ( top - bottom ) ), 0, 1
		);
	}

	template <typename R>
	static constexpr auto rotateX( const R radian ) noexcept {
		const auto c = math::cos( radian );
		const auto s = math::sin( radian );

		return mat4<Type>(
			1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1
		);
	}

	template <typename R>
	static constexpr auto rotateY( const R radian ) noexcept {
		const auto c = math::cos( radian );
		const auto s = math::sin( radian );

		return mat4<Type>(
			c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1
		);
	}

	template <typename R>
	static constexpr auto rotateZ( const R radian ) noexcept {
		const auto c = math::cos( radian );
		const auto s = math::sin( radian );

		return mat4<Type>(
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	template <typename V = Type>
	static constexpr auto translate( const vec3<V>& vector ) noexcept {
		return mat4<Type>(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			vector.x, vector.y, vector.z, 1
		);
	}

	template <typename M = Type, typename V = Type>
	static constexpr auto translate( const mat4<M>& m, const vec3<V>& vector ) noexcept {
		auto result = m;
		result.xyzw = m.abcd * vector.x + m.efgh * vector.y + m.ijkl * vector.z + m.xyzw.w;
		return result;
	}

	template <typename M = Type>
	static constexpr auto inverse( const mat4<M>& m ) noexcept {
		const auto coef00 = m.ijkl.z * m.xyzw.w - m.xyzw.z * m.ijkl.w;
		const auto coef02 = m.efgh.z * m.xyzw.w - m.xyzw.z * m.efgh.w;
		const auto coef03 = m.efgh.z * m.ijkl.w - m.ijkl.z * m.efgh.w;

		const auto coef04 = m.ijkl.y * m.xyzw.w - m.xyzw.y * m.ijkl.w;
		const auto coef06 = m.efgh.y * m.xyzw.w - m.xyzw.y * m.efgh.w;
		const auto coef07 = m.efgh.y * m.ijkl.w - m.ijkl.y * m.efgh.w;

		const auto coef08 = m.ijkl.y * m.xyzw.z - m.xyzw.y * m.ijkl.z;
		const auto coef10 = m.efgh.y * m.xyzw.z - m.xyzw.y * m.efgh.z;
		const auto coef11 = m.efgh.y * m.ijkl.z - m.ijkl.y * m.efgh.z;

		const auto coef12 = m.ijkl.x * m.xyzw.w - m.xyzw.x * m.ijkl.w;
		const auto coef14 = m.efgh.x * m.xyzw.w - m.xyzw.x * m.efgh.w;
		const auto coef15 = m.efgh.x * m.ijkl.w - m.ijkl.x * m.efgh.w;

		const auto coef16 = m.ijkl.x * m.xyzw.z - m.xyzw.x * m.ijkl.z;
		const auto coef18 = m.efgh.x * m.xyzw.z - m.xyzw.x * m.efgh.z;
		const auto coef19 = m.efgh.x * m.ijkl.z - m.ijkl.x * m.efgh.z;

		const auto coef20 = m.ijkl.x * m.xyzw.y - m.xyzw.x * m.ijkl.y;
		const auto coef22 = m.efgh.x * m.xyzw.y - m.xyzw.x * m.efgh.y;
		const auto coef23 = m.efgh.x * m.ijkl.y - m.ijkl.x * m.efgh.y;

		const auto fac0 = vec4<Type> { coef00, coef00, coef02, coef03 };
		const auto fac1 = vec4<Type> { coef04, coef04, coef06, coef07 };
		const auto fac2 = vec4<Type> { coef08, coef08, coef10, coef11 };
		const auto fac3 = vec4<Type> { coef12, coef12, coef14, coef15 };
		const auto fac4 = vec4<Type> { coef16, coef16, coef18, coef19 };
		const auto fac5 = vec4<Type> { coef20, coef20, coef22, coef23 };

		const auto vect0 = vec4<Type> { m.efgh.x, m.abcd.x, m.abcd.x, m.abcd.x };
		const auto vect1 = vec4<Type> { m.efgh.y, m.abcd.y, m.abcd.y, m.abcd.y };
		const auto vect2 = vec4<Type> { m.efgh.z, m.abcd.z, m.abcd.z, m.abcd.z };
		const auto vect3 = vec4<Type> { m.efgh.w, m.abcd.w, m.abcd.w, m.abcd.w };

		const auto inv0 = vec4<Type> { vect1 * fac0 - vect2 * fac1 + vect3 * fac2 };
		const auto inv1 = vec4<Type> { vect0 * fac0 - vect2 * fac3 + vect3 * fac4 };
		const auto inv2 = vec4<Type> { vect0 * fac1 - vect1 * fac3 + vect3 * fac5 };
		const auto inv3 = vec4<Type> { vect0 * fac2 - vect1 * fac4 + vect2 * fac5 };

		const auto signA = vec4<Type> { +1, -1, +1, -1 };
		const auto signB = vec4<Type> { -1, +1, -1, +1 };

		const auto inver = mat4<Type> { inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB };

		const auto row0 = vec4<Type> { inver.abcd.x, inver.efgh.x, inver.ijkl.x, inver.xyzw.x };

		const auto dot0 = m.abcd * row0;
		const auto dot1 = ( dot0.x + dot0.y ) + ( dot0.z + dot0.w );

		const auto oneOverDeterminant = static_cast<Type>( 1 ) / dot1;

		return inver * oneOverDeterminant;
	}

	using value_type = Type;
	using size_type = uint32;

	using type = mat4<Type>;

	vec4<Type>	abcd;
	vec4<Type>	efgh;
	vec4<Type>	ijkl;
	vec4<Type>	xyzw;

	constexpr mat4() noexcept : 
		abcd( { 1, 0, 0, 0 } ), 
		efgh( { 0, 1, 0, 0 } ),
		ijkl( { 0, 0, 1, 0 } ),
		xyzw( { 0, 0, 0, 1 } ) {}

	template <typename M>
	constexpr mat4( const mat4<M>& other ) noexcept : 
		abcd( other.abcd ),
		efgh( other.efgh ),
		ijkl( other.ijkl ),
		xyzw( other.xyzw ) {}

	template <typename S>
	constexpr mat4( S scalar ) noexcept : 
		abcd( { scalar, 0, 0, 0 } ), 
		efgh( { 0, scalar, 0, 0 } ), 
		ijkl( { 0, 0, scalar, 0 } ), 
		xyzw( { 0, 0, 0, scalar } ) {}

	template <typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename X, typename Y, typename Z, typename W>
	constexpr mat4( A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, X x, Y y, Z z, W w ) noexcept : 
		abcd( { a, b, c, d } ),
		efgh( { e, f, g, h } ),
		ijkl( { i, j, k, l } ),
		xyzw( { x, y, z, w } ) {}

	template <typename V0, typename V1, typename V2, typename V3>
	constexpr mat4( const vec4<V0>& v0, const vec4<V1>& v1, const vec4<V2>& v2, const vec4<V3>& v3 ) noexcept : 
		abcd( v0 ),
		efgh( v1 ),
		ijkl( v2 ),
		xyzw( v3 ) {}

	constexpr auto& operator []( size_type i ) noexcept {
		assert( i >= 0 && i < 4 );

		switch ( i ) {
		default:
		case 0:
			return abcd;
		case 1:
			return efgh;
		case 2:
			return ijkl;
		case 3:
			return xyzw;
		}
	}

	constexpr const auto& operator []( size_type i ) const noexcept {
		assert( i >= 0 && i < 4 );

		switch ( i ) {
		default:
		case 0:
			return abcd;
		case 1:
			return efgh;
		case 2:
			return ijkl;
		case 3:
			return xyzw;
		}
	}

	template <typename OType>
	constexpr auto& operator =( const mat4<OType>& other ) noexcept {
		abcd = other.abcd;
		efgh = other.efgh;
		ijkl = other.ijkl;
		xyzw = other.xyzw;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( OType scalar ) noexcept {
		abcd += scalar;
		efgh += scalar;
		ijkl += scalar;
		xyzw += scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const mat4<OType>& other ) noexcept {
		abcd += other.abcd;
		efgh += other.efgh;
		ijkl += other.ijkl;
		xyzw += other.xyzw;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( OType scalar ) noexcept {
		abcd -= scalar;
		efgh -= scalar;
		ijkl -= scalar;
		xyzw -= scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const mat4<OType>& other ) noexcept {
		abcd -= other.abcd;
		efgh -= other.efgh;
		ijkl -= other.ijkl;
		xyzw -= other.xyzw;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( OType scalar ) noexcept {
		abcd *= scalar;
		efgh *= scalar;
		ijkl *= scalar;
		xyzw *= scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( OType scalar ) noexcept {
		abcd /= scalar;
		efgh /= scalar;
		ijkl /= scalar;
		xyzw /= scalar;
		return *this;
	}

	constexpr auto& operator ++() noexcept {
		++abcd;
		++efgh;
		++ijkl;
		++xyzw;
		return *this;
	}

	constexpr auto& operator --() noexcept {
		--abcd;
		--efgh;
		--ijkl;
		--xyzw;
		return *this;
	}

	constexpr auto& operator ++( int ) noexcept {
		const auto r = *this;
		++abcd;
		++efgh;
		++ijkl;
		++xyzw;
		return r;
	}

	constexpr auto& operator --( int ) noexcept {
		const auto r = *this;
		--abcd;
		--efgh;
		--ijkl;
		--xyzw;
		return r;
	}
};

template <typename OType>
constexpr const auto& operator +( const mat4<OType>& m ) noexcept {
	return m;
}

template <typename OType>
constexpr auto operator -( const mat4<OType>& m ) noexcept {
	return mat4<OType>( -m.abcd, -m.efgh, -m.ijkl, -m.xyzw );
}

template <typename OType, typename S>
constexpr auto operator +( const mat4<OType>& m, S s ) noexcept {
	return mat4<OType>( m.abcd + s, m.efgh + s, m.ijkl + s, m.xyzw + s );
}

template <typename AT, typename BT>
constexpr auto operator +( const mat4<AT>& a, const mat4<BT>& b ) noexcept {
	return mat4<AT>( a.abcd + b.abcd, a.efgh + b.efgh, a.ijkl + b.ijkl, a.xyzw + b.xyzw );
}

template <typename OType, typename S>
constexpr auto operator -( const mat4<OType>& m, S s ) noexcept {
	return mat4<OType>( m.abcd - s, m.efgh - s, m.ijkl - s, m.xyzw - s );
}

template <typename AT, typename BT>
constexpr auto operator -( const mat4<AT>& a, const mat4<BT>& b ) noexcept {
	return mat4<AT>( a.abcd - b.abcd, a.efgh - b.efgh, a.ijkl - b.ijkl, a.xyzw - b.xyzw );
}

template <typename OType, typename S>
constexpr auto operator *( const mat4<OType>& m, S s ) noexcept {
	return mat4<OType>( m.abcd * s, m.efgh * s, m.ijkl * s, m.xyzw * s );
}

template <typename S, typename OType>
constexpr auto operator *( S s, const mat4<OType>& m ) noexcept {
	return mat4<OType>( m.abcd * s, m.efgh * s, m.ijkl * s, m.xyzw * s );
}

template <typename OType, typename VType>
constexpr auto operator *( const mat4<OType>& m, const vec4<VType>& v ) noexcept {
	return vec4<VType>(
		m.abcd.x * v.x + m.efgh.x * v.y + m.ijkl.x * v.z + m.xyzw.x * v.w,
		m.abcd.y * v.x + m.efgh.y * v.y + m.ijkl.y * v.z + m.xyzw.y * v.w,
		m.abcd.z * v.x + m.efgh.z * v.y + m.ijkl.z * v.z + m.xyzw.z * v.w,
		m.abcd.w * v.x + m.efgh.w * v.y + m.ijkl.w * v.z + m.xyzw.w * v.w );
}

template <typename OType, typename VType>
constexpr auto operator *( const vec4<VType>& v, const mat4<OType>& m ) noexcept {
	return vec4<VType>(
		v.x * m.abcd.x + v.y * m.abcd.y + v.z * m.abcd.z + v.w * m.abcd.w,
		v.x * m.efgh.x + v.y * m.efgh.y + v.z * m.efgh.z + v.w * m.efgh.w,
		v.x * m.ijkl.x + v.y * m.ijkl.y + v.z * m.ijkl.z + v.w * m.ijkl.w,
		v.x * m.xyzw.x + v.y * m.xyzw.y + v.z * m.xyzw.z + v.w * m.xyzw.w );
}

template <typename AT, typename BT>
constexpr auto operator *( const mat4<AT>& m1, const mat4<BT>& m2 ) noexcept {
	return mat4<AT>(
		m1.abcd.x * m2.abcd.x + m1.efgh.x * m2.abcd.y + m1.ijkl.x * m2.abcd.z + m1.xyzw.x * m2.abcd.w,
		m1.abcd.y * m2.abcd.x + m1.efgh.y * m2.abcd.y + m1.ijkl.y * m2.abcd.z + m1.xyzw.y * m2.abcd.w,
		m1.abcd.z * m2.abcd.x + m1.efgh.z * m2.abcd.y + m1.ijkl.z * m2.abcd.z + m1.xyzw.z * m2.abcd.w,
		m1.abcd.w * m2.abcd.x + m1.efgh.w * m2.abcd.y + m1.ijkl.w * m2.abcd.z + m1.xyzw.w * m2.abcd.w,
		m1.abcd.x * m2.efgh.x + m1.efgh.x * m2.efgh.y + m1.ijkl.x * m2.efgh.z + m1.xyzw.x * m2.efgh.w,
		m1.abcd.y * m2.efgh.x + m1.efgh.y * m2.efgh.y + m1.ijkl.y * m2.efgh.z + m1.xyzw.y * m2.efgh.w,
		m1.abcd.z * m2.efgh.x + m1.efgh.z * m2.efgh.y + m1.ijkl.z * m2.efgh.z + m1.xyzw.z * m2.efgh.w,
		m1.abcd.w * m2.efgh.x + m1.efgh.w * m2.efgh.y + m1.ijkl.w * m2.efgh.z + m1.xyzw.w * m2.efgh.w,
		m1.abcd.x * m2.ijkl.x + m1.efgh.x * m2.ijkl.y + m1.ijkl.x * m2.ijkl.z + m1.xyzw.x * m2.ijkl.w,
		m1.abcd.y * m2.ijkl.x + m1.efgh.y * m2.ijkl.y + m1.ijkl.y * m2.ijkl.z + m1.xyzw.y * m2.ijkl.w,
		m1.abcd.z * m2.ijkl.x + m1.efgh.z * m2.ijkl.y + m1.ijkl.z * m2.ijkl.z + m1.xyzw.z * m2.ijkl.w,
		m1.abcd.w * m2.ijkl.x + m1.efgh.w * m2.ijkl.y + m1.ijkl.w * m2.ijkl.z + m1.xyzw.w * m2.ijkl.w,
		m1.abcd.x * m2.xyzw.x + m1.efgh.x * m2.xyzw.y + m1.ijkl.x * m2.xyzw.z + m1.xyzw.x * m2.xyzw.w,
		m1.abcd.y * m2.xyzw.x + m1.efgh.y * m2.xyzw.y + m1.ijkl.y * m2.xyzw.z + m1.xyzw.y * m2.xyzw.w,
		m1.abcd.z * m2.xyzw.x + m1.efgh.z * m2.xyzw.y + m1.ijkl.z * m2.xyzw.z + m1.xyzw.z * m2.xyzw.w,
		m1.abcd.w * m2.xyzw.x + m1.efgh.w * m2.xyzw.y + m1.ijkl.w * m2.xyzw.z + m1.xyzw.w * m2.xyzw.w
	);
}

template <typename OType, typename S>
constexpr auto operator /( const mat4<OType>& m, S s ) noexcept {
	return mat4<OType>( m.abcd / s, m.efgh / s, m.ijkl / s, m.xyzw / s );
}

template <typename S, typename OType>
constexpr auto operator /( S s, const mat4<OType>& m ) noexcept {
	return mat4<OType>( s / m.abcd, s / m.efgh, s / m.ijkl, s / m.xyzw );
}

template <typename AT, typename BT>
constexpr auto operator ==( const mat4<AT>& m1, const mat4<BT>& m2 ) noexcept {
	return m1.abcd == m2.abcd && m1.efgh == m2.efgh && m1.ijkl == m2.ijkl && m1.xyzw == m2.xyzw;
}

template <typename AT, typename BT>
constexpr auto operator !=( const mat4<AT>& m1, const mat4<BT>& m2 ) noexcept {
	return !( m1 == m2 );
}

} // gba

#endif // define GBAXX_MAT4_HPP
