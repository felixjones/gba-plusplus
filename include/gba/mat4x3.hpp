#ifndef GBAXX_MAT4X3_HPP
#define GBAXX_MAT4X3_HPP

#include <cassert>

#include <gba/int.hpp>
#include <gba/math.hpp>
#include <gba/vec3.hpp>

namespace gba {

template <typename Type>
struct mat4x3 {
	using value_type = Type;
	using size_type = uint32;

	using type = mat4x3<Type>;

	vec3<Type>	abc;
	vec3<Type>	def;
	vec3<Type>	ghi;
	vec3<Type>	xyz;

	template <typename E = Type, typename C = Type, typename U = Type>
	static constexpr auto lookAt( const vec3<E>& eye, const vec3<C>& center, const vec3<U>& up ) noexcept {
		const auto f = math::normalize( center - eye );
		const auto s = math::normalize( math::cross( f, up ) );
		const auto u = math::cross( s, f );

		return mat4x3<Type>(
			s.x, u.x, -f.x,
			s.y, u.y, -f.y,
			s.z, u.z, -f.z,
			-math::dot( s, eye ), -math::dot( u, eye ), math::dot( f, eye )
		);
	}

	constexpr mat4x3() noexcept : 
		abc( { 1, 0, 0 } ), 
		def( { 0, 1, 0 } ),
		ghi( { 0, 0, 1 } ),
		xyz( { 0, 0, 0 } ) {}

	template <typename M>
	constexpr mat4x3( const mat4x3<M>& other ) noexcept : 
		abc( other.abc ),
		def( other.def ),
		ghi( other.ghi ),
		xyz( other.xyz ) {}

	template <typename S>
	constexpr mat4x3( S scalar ) noexcept : 
		abc( { scalar, 0, 0 } ), 
		def( { 0, scalar, 0 } ), 
		ghi( { 0, 0, scalar } ), 
		xyz( { 0, 0, 0 } ) {}

	template <typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename X, typename Y, typename Z>
	constexpr mat4x3( A a, B b, C c, D d, E e, F f, G g, H h, I i, X x, Y y, Z z ) noexcept : 
		abc( { a, b, c } ),
		def( { d, e, f } ),
		ghi( { g, h, i } ),
		xyz( { x, y, z } ) {}

	template <typename V0, typename V1, typename V2, typename V3>
	constexpr mat4x3( const vec3<V0>& v0, const vec3<V1>& v1, const vec3<V2>& v2, const vec3<V3>& v3 ) noexcept : 
		abc( v0 ),
		def( v1 ),
		ghi( v2 ),
		xyz( v3 ) {}

	constexpr auto& operator []( size_type i ) noexcept {
		assert( i >= 0 && i < 4 );

		switch ( i ) {
		default:
		case 0:
			return abc;
		case 1:
			return def;
		case 2:
			return ghi;
		case 3:
			return xyz;
		}
	}

	constexpr const auto& operator []( size_type i ) const noexcept {
		assert( i >= 0 && i < 4 );

		switch ( i ) {
		default:
		case 0:
			return abc;
		case 1:
			return def;
		case 2:
			return ghi;
		case 3:
			return xyz;
		}
	}

	template <typename OType>
	constexpr auto& operator =( const mat4x3<OType>& other ) noexcept {
		abc = other.abc;
		def = other.def;
		ghi = other.ghi;
		xyz = other.xyz;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( OType scalar ) noexcept {
		abc += scalar;
		def += scalar;
		ghi += scalar;
		xyz += scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const mat4x3<OType>& other ) noexcept {
		abc += other.abc;
		def += other.def;
		ghi += other.ghi;
		xyz += other.xyz;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( OType scalar ) noexcept {
		abc -= scalar;
		def -= scalar;
		ghi -= scalar;
		xyz -= scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const mat4x3<OType>& other ) noexcept {
		abc -= other.abc;
		def -= other.def;
		ghi -= other.ghi;
		xyz -= other.xyz;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( OType scalar ) noexcept {
		abc *= scalar;
		def *= scalar;
		ghi *= scalar;
		xyz *= scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( OType scalar ) noexcept {
		abc /= scalar;
		def /= scalar;
		ghi /= scalar;
		xyz /= scalar;
		return *this;
	}

	constexpr auto& operator ++() noexcept {
		++abc;
		++def;
		++ghi;
		++xyz;
		return *this;
	}

	constexpr auto& operator --() noexcept {
		--abc;
		--def;
		--ghi;
		--xyz;
		return *this;
	}

	constexpr auto& operator ++( int ) noexcept {
		const auto r = *this;
		++abc;
		++def;
		++ghi;
		++xyz;
		return r;
	}

	constexpr auto& operator --( int ) noexcept {
		const auto r = *this;
		--abc;
		--def;
		--ghi;
		--xyz;
		return r;
	}
};

template <typename OType>
constexpr const auto& operator +( const mat4x3<OType>& m ) noexcept {
	return m;
}

template <typename OType>
constexpr auto operator -( const mat4x3<OType>& m ) noexcept {
	return mat4x3<OType>( -m.abc, -m.def, -m.ghi, -m.xyz );
}

template <typename OType, typename S>
constexpr auto operator +( const mat4x3<OType>& m, S s ) noexcept {
	return mat4x3<OType>( m.abc + s, m.def + s, m.ghi + s, m.xyz + s );
}

template <typename AT, typename BT>
constexpr auto operator +( const mat4x3<AT>& a, const mat4x3<BT>& b ) noexcept {
	return mat4x3<AT>( a.abc + b.abc, a.def + b.def, a.ghi + b.ghi, a.xyz + b.xyz );
}

template <typename OType, typename S>
constexpr auto operator -( const mat4x3<OType>& m, S s ) noexcept {
	return mat4x3<OType>( m.abc - s, m.def - s, m.ghi - s, m.xyz - s );
}

template <typename AT, typename BT>
constexpr auto operator -( const mat4x3<AT>& a, const mat4x3<BT>& b ) noexcept {
	return mat4x3<AT>( a.abc - b.abc, a.def - b.def, a.ghi - b.ghi, a.xyz - b.xyz );
}

template <typename OType, typename S>
constexpr auto operator *( const mat4x3<OType>& m, S s ) noexcept {
	return mat4x3<OType>( m.abc * s, m.def * s, m.ghi * s, m.xyz * s );
}

template <typename S, typename OType>
constexpr auto operator *( S s, const mat4x3<OType>& m ) noexcept {
	return mat4x3<OType>( m.abc * s, m.def * s, m.ghi * s, m.xyz * s );
}

template <typename OType, typename VType>
constexpr auto operator *( const mat4x3<OType>& m, const vec3<VType>& v ) noexcept {
	return vec3<VType>(
		m.abc[0] * v.x + m.def[0] * v.y + m.ghi[0] * v.z,
		m.abc[1] * v.x + m.def[1] * v.y + m.ghi[1] * v.z,
		m.abc[2] * v.x + m.def[2] * v.y + m.ghi[2] * v.z);
}

template <typename OType, typename VType>
constexpr auto operator *( const vec3<VType>& v, const mat4x3<OType>& m ) noexcept {
	return vec3<VType>(
		v.x * m.abc[0] + v.y * m.abc[1] + v.z * m.abc[2],
		v.x * m.def[0] + v.y * m.def[1] + v.z * m.def[2],
		v.x * m.ghi[0] + v.y * m.ghi[1] + v.z * m.ghi[2]);
}

template <typename AT, typename BT>
constexpr auto operator *( const mat4x3<AT>& m1, const mat4x3<BT>& m2 ) noexcept {
	return mat4x3<AT>(
		m1.abc[0] * m2.abc[0] + m1.def[0] * m2.abc[1] + m1.ghi[0] * m2.abc[2] /*+ m1.xyz[0] * m2.abc[3]*/,
		m1.abc[1] * m2.abc[0] + m1.def[1] * m2.abc[1] + m1.ghi[1] * m2.abc[2] /*+ m1.xyz[1] * m2.abc[3]*/,
		m1.abc[2] * m2.abc[0] + m1.def[2] * m2.abc[1] + m1.ghi[2] * m2.abc[2] /*+ m1.xyz[2] * m2.abc[3]*/,
		m1.abc[0] * m2.def[0] + m1.def[0] * m2.def[1] + m1.ghi[0] * m2.def[2] /*+ m1.xyz[0] * m2.def[3]*/,
		m1.abc[1] * m2.def[0] + m1.def[1] * m2.def[1] + m1.ghi[1] * m2.def[2] /*+ m1.xyz[1] * m2.def[3]*/,
		m1.abc[2] * m2.def[0] + m1.def[2] * m2.def[1] + m1.ghi[2] * m2.def[2] /*+ m1.xyz[2] * m2.def[3]*/,
		m1.abc[0] * m2.ghi[0] + m1.def[0] * m2.ghi[1] + m1.ghi[0] * m2.ghi[2] /*+ m1.xyz[0] * m2.ghi[3]*/,
		m1.abc[1] * m2.ghi[0] + m1.def[1] * m2.ghi[1] + m1.ghi[1] * m2.ghi[2] /*+ m1.xyz[1] * m2.ghi[3]*/,
		m1.abc[2] * m2.ghi[0] + m1.def[2] * m2.ghi[1] + m1.ghi[2] * m2.ghi[2] /*+ m1.xyz[2] * m2.ghi[3]*/,
		m1.abc[0] * m2.xyz[0] + m1.def[0] * m2.xyz[1] + m1.ghi[0] * m2.xyz[2] + m1.xyz[0] /** m2.xyz[3]*/,
		m1.abc[1] * m2.xyz[0] + m1.def[1] * m2.xyz[1] + m1.ghi[1] * m2.xyz[2] + m1.xyz[1] /** m2.xyz[3]*/,
		m1.abc[2] * m2.xyz[0] + m1.def[2] * m2.xyz[1] + m1.ghi[2] * m2.xyz[2] + m1.xyz[2] /** m2.xyz[3]*/);
}

template <typename OType, typename S>
constexpr auto operator /( const mat4x3<OType>& m, S s ) noexcept {
	return mat4x3<OType>( m.abc / s, m.def / s, m.ghi / s, m.xyz / s );
}

template <typename S, typename OType>
constexpr auto operator /( S s, const mat4x3<OType>& m ) noexcept {
	return mat4x3<OType>( s / m.abc, s / m.def, s / m.ghi, s / m.xyz );
}

template <typename AT, typename BT>
constexpr auto operator ==( const mat4x3<AT>& m1, const mat4x3<BT>& m2 ) noexcept {
	return m1.abc == m2.abc && m1.def == m2.def && m1.ghi == m2.ghi && m1.xyz == m2.xyz;
}

template <typename AT, typename BT>
constexpr auto operator !=( const mat4x3<AT>& m1, const mat4x3<BT>& m2 ) noexcept {
	return !( m1 == m2 );
}

} // gba

#endif // define GBAXX_MAT4X3_HPP
