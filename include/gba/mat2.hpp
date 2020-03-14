#ifndef GBAXX_MAT2_HPP
#define GBAXX_MAT2_HPP

#include <cassert>

#include <gba/int.hpp>
#include <gba/vec2.hpp>

namespace gba {

template <typename Type>
struct mat2 {
	using value_type = Type;
	using size_type = uint32;

	using type = mat2<Type>;

	vec2<Type>	ab;
	vec2<Type>	cd;

	constexpr mat2() noexcept : ab( { 1, 0 } ), cd( { 0, 1 } ) {}

	template <typename M>
	constexpr mat2( const mat2<M>& other ) noexcept : ab( other.ab ), cd( other.cd ) {}

	template <typename S>
	constexpr mat2( S scalar ) noexcept : ab( { scalar, 0 } ), cd( { 0, scalar } ) {}

	template <typename A, typename B, typename C, typename D>
	constexpr mat2( A a, B b, C c, D d ) noexcept : 
		ab( { a, b } ),
		cd( { c, d } ) {}

	template <typename V0, typename V1>
	constexpr mat2( const vec2<V0>& v0, const vec2<V1>& v1 ) noexcept : 
		ab( v0 ),
		cd( v1 ) {}

	constexpr auto& operator []( size_type i ) noexcept {
		assert( i >= 0 && i < 2 );

		switch ( i ) {
		default:
		case 0:
			return ab;
		case 1:
			return cd;
		}
	}

	constexpr const auto& operator []( size_type i ) const noexcept {
		assert( i >= 0 && i < 2 );

		switch ( i ) {
		default:
		case 0:
			return ab;
		case 1:
			return cd;
		}
	}

	template <typename OType>
	constexpr auto& operator =( const mat2<OType>& other ) noexcept {
		ab = other.ab;
		cd = other.cd;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( OType scalar ) noexcept {
		ab += scalar;
		cd += scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const mat2<OType>& other ) noexcept {
		ab += other.ab;
		cd += other.cd;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( OType scalar ) noexcept {
		ab -= scalar;
		cd -= scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const mat2<OType>& other ) noexcept {
		ab -= other.ab;
		cd -= other.cd;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( OType scalar ) noexcept {
		ab *= scalar;
		cd *= scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( OType scalar ) noexcept {
		ab /= scalar;
		cd /= scalar;
		return *this;
	}

	constexpr auto& operator ++() noexcept {
		++ab;
		++cd;
		return *this;
	}

	constexpr auto& operator --() noexcept {
		--ab;
		--cd;
		return *this;
	}

	constexpr auto& operator ++( int ) noexcept {
		const auto r = *this;
		++ab;
		++cd;
		return r;
	}

	constexpr auto& operator --( int ) noexcept {
		const auto r = *this;
		--ab;
		--cd;
		return r;
	}
};

template <typename OType>
constexpr const auto& operator +( const mat2<OType>& m ) noexcept {
	return m;
}

template <typename OType>
constexpr const auto& operator -( const mat2<OType>& m ) noexcept {
	return mat2<OType>( -m.ab, -m.cd );
}

template <typename OType, typename S>
constexpr auto operator +( const mat2<OType>& m, S s ) noexcept {
	return mat2<OType>( m.ab + s, m.cd + s );
}

template <typename AT, typename BT>
constexpr auto operator +( const mat2<AT>& a, const mat2<BT>& b ) noexcept {
	return mat2<AT>( a.ab + b.ab, a.cd + b.cd );
}

template <typename OType, typename S>
constexpr auto operator -( const mat2<OType>& m, S s ) noexcept {
	return mat2<OType>( m.ab - s, m.cd - s );
}

template <typename AT, typename BT>
constexpr auto operator -( const mat2<AT>& a, const mat2<BT>& b ) noexcept {
	return mat2<AT>( a.ab - b.ab, a.cd - b.cd );
}

template <typename OType, typename S>
constexpr auto operator *( const mat2<OType>& m, S s ) noexcept {
	return mat2<OType>( m.ab * s, m.cd * s );
}

template <typename S, typename OType>
constexpr auto operator *( S s, const mat2<OType>& m ) noexcept {
	return mat2<OType>( m.ab * s, m.cd * s );
}

template <typename OType, typename VType>
constexpr auto operator *( const mat2<OType>& m, const vec2<VType>& v ) noexcept {
	return vec2<VType>(
		m.ab[0] * v.x + m.cd[0] * v.y,
		m.ab[1] * v.x + m.cd[1] * v.y);
}

template <typename OType, typename VType>
constexpr auto operator *( const vec2<VType>& v, const mat2<OType>& m ) noexcept {
	return vec2<VType>(
		v.x * m.ab[0] + v.y * m.ab[1],
		v.x * m.cd[0] + v.y * m.cd[1]);
}

template <typename AT, typename BT>
constexpr auto operator *( const mat2<AT>& m1, const mat2<BT>& m2 ) noexcept {
	return mat2<AT>(
		m1.ab[0] * m2.ab[0] + m1.cd[0] * m2.ab[1],
		m1.ab[1] * m2.ab[0] + m1.cd[1] * m2.ab[1],
		m1.ab[0] * m2.cd[0] + m1.cd[0] * m2.cd[1],
		m1.ab[1] * m2.cd[0] + m1.cd[1] * m2.cd[1]);
}

template <typename OType, typename S>
constexpr auto operator /( const mat2<OType>& m, S s ) noexcept {
	return mat2<OType>( m.ab / s, m.cd / s, m.xy / s );
}

template <typename S, typename OType>
constexpr auto operator /( S s, const mat2<OType>& m ) noexcept {
	return mat2<OType>( s / m.ab, s / m.cd, s / m.xy );
}

template <typename AT, typename BT>
constexpr auto operator ==( const mat2<AT>& m1, const mat2<BT>& m2 ) noexcept {
	return m1.ab == m2.ab && m1.cd == m2.cd && m1.xy == m2.xy;
}

template <typename AT, typename BT>
constexpr auto operator !=( const mat2<AT>& m1, const mat2<BT>& m2 ) noexcept {
	return !( m1 == m2 );
}

} // gba

#endif // define GBAXX_MAT2_HPP
