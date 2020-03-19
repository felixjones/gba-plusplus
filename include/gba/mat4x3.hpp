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
		const auto s = math::cross( up, f );
		const auto u = math::cross( f, s );

		return mat4x3<Type>(
			s.x, u.x, f.x,
			s.y, u.y, f.y,
			s.z, u.z, f.z,
			eye.x, eye.y, eye.z
		);
	}

	template <typename R, typename V>
	static constexpr mat4x3<Type> rotate( const R radian, const vec3<V>& axis ) noexcept {
		const auto c = math::cos( radian );
		const auto s = math::sin( radian );

		const auto temp = axis * ( 1 - c );

		const auto abc = vec3<Type> { c + temp.x * axis.x, temp.x * axis.y + s * axis.z, temp.x * axis.z - s * axis.y };
		const auto def = vec3<Type> { temp.y * axis.x - s * axis.z, c + temp.y * axis.y, temp.y * axis.z + s * axis.x };
		const auto ghi = vec3<Type> { temp.z * axis.x + s * axis.y, temp.z * axis.y - s * axis.x, c + temp.z * axis.z };

		constexpr auto iAbc = vec3<Type> { 1, 0, 0 };
		constexpr auto iDef = vec3<Type> { 0, 1, 0 };
		constexpr auto iGhi = vec3<Type> { 0, 0, 1 };

		return mat4x3<Type>(
			iAbc * abc.x + iDef * abc.y + iGhi * abc.z,
			iAbc * def.x + iDef * def.y + iGhi * def.z,
			iAbc * ghi.x + iDef * ghi.y + iGhi * ghi.z,
			vec3<Type> { 0, 0, 0 }
			);
	}

	template <typename M, typename R, typename V>
	static constexpr mat4x3<Type> rotate( const mat4x3<M>& m, const R radian, const vec3<V>& axis ) noexcept {
		const auto c = math::cos( radian );
		const auto s = math::sin( radian );

		const auto temp = axis * ( 1 - c );

		const auto abc = vec3<Type> { c + temp.x * axis.x, temp.x * axis.y + s * axis.z, temp.x * axis.z - s * axis.y };
		const auto def = vec3<Type> { temp.y * axis.x - s * axis.z, c + temp.y * axis.y, temp.y * axis.z + s * axis.x };
		const auto ghi = vec3<Type> { temp.z * axis.x + s * axis.y, temp.z * axis.y - s * axis.x, c + temp.z * axis.z };

		return mat4x3<Type>(
			m.abc * abc.x + m.def * abc.y + m.ghi * abc.z,
			m.abc * def.x + m.def * def.y + m.ghi * def.z,
			m.abc * ghi.x + m.def * ghi.y + m.ghi * ghi.z,
			m.xyz
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
		m.abc.x * v.x + m.def.x * v.y + m.ghi.x * v.z,
		m.abc.y * v.x + m.def.y * v.y + m.ghi.y * v.z,
		m.abc.z * v.x + m.def.z * v.y + m.ghi.z * v.z);
}

template <typename OType, typename VType>
constexpr auto operator *( const vec3<VType>& v, const mat4x3<OType>& m ) noexcept {
	return vec3<VType>(
		v.x * m.abc.x + v.y * m.abc.y + v.z * m.abc.z,
		v.x * m.def.x + v.y * m.def.y + v.z * m.def.z,
		v.x * m.ghi.x + v.y * m.ghi.y + v.z * m.ghi.z);
}

template <typename AT, typename BT>
constexpr auto operator *( const mat4x3<AT>& m1, const mat4x3<BT>& m2 ) noexcept {
	return mat4x3<AT>(
		m1.abc.x * m2.abc.x + m1.def.x * m2.abc.y + m1.ghi.x * m2.abc.z /*+ m1.xyz.x * m2.abc.w*/,
		m1.abc.y * m2.abc.x + m1.def.y * m2.abc.y + m1.ghi.y * m2.abc.z /*+ m1.xyz.y * m2.abc.w*/,
		m1.abc.z * m2.abc.x + m1.def.z * m2.abc.y + m1.ghi.z * m2.abc.z /*+ m1.xyz.z * m2.abc.w*/,
		m1.abc.x * m2.def.x + m1.def.x * m2.def.y + m1.ghi.x * m2.def.z /*+ m1.xyz.x * m2.def.w*/,
		m1.abc.y * m2.def.x + m1.def.y * m2.def.y + m1.ghi.y * m2.def.z /*+ m1.xyz.y * m2.def.w*/,
		m1.abc.z * m2.def.x + m1.def.z * m2.def.y + m1.ghi.z * m2.def.z /*+ m1.xyz.z * m2.def.w*/,
		m1.abc.x * m2.ghi.x + m1.def.x * m2.ghi.y + m1.ghi.x * m2.ghi.z /*+ m1.xyz.x * m2.ghi.w*/,
		m1.abc.y * m2.ghi.x + m1.def.y * m2.ghi.y + m1.ghi.y * m2.ghi.z /*+ m1.xyz.y * m2.ghi.w*/,
		m1.abc.z * m2.ghi.x + m1.def.z * m2.ghi.y + m1.ghi.z * m2.ghi.z /*+ m1.xyz.z * m2.ghi.w*/,
		m1.abc.x * m2.xyz.x + m1.def.x * m2.xyz.y + m1.ghi.x * m2.xyz.z + m1.xyz.x /** m2.xyz.w*/,
		m1.abc.y * m2.xyz.x + m1.def.y * m2.xyz.y + m1.ghi.y * m2.xyz.z + m1.xyz.y /** m2.xyz.w*/,
		m1.abc.z * m2.xyz.x + m1.def.z * m2.xyz.y + m1.ghi.z * m2.xyz.z + m1.xyz.z /** m2.xyz.w*/);
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
