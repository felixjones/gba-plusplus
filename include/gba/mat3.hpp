#ifndef GBAXX_MAT3_HPP
#define GBAXX_MAT3_HPP

#include <cassert>

#include <gba/int.hpp>
#include <gba/vec3.hpp>

namespace gba {

template <typename Type>
struct mat3 {
	using value_type = Type;
	using size_type = uint32;

	using type = mat3<Type>;

	vec3<Type>	abc;
	vec3<Type>	def;
	vec3<Type>	ghi;

	template <typename R>
	static constexpr mat3<Type> rotateX( const R radian ) noexcept {
		const auto c = math::cos( radian );
		const auto s = math::sin( radian );

		return mat3<Type>(
			1, 0, 0,
			0, c, s,
			0, -s, c
		);
	}

	template <typename R>
	static constexpr mat3<Type> rotateY( const R radian ) noexcept {
		const auto c = math::cos( radian );
		const auto s = math::sin( radian );

		return mat3<Type>(
			c, 0, -s,
			0, 1, 0,
			s, 0, c
		);
	}

	template <typename R>
	static constexpr mat3<Type> rotateZ( const R radian ) noexcept {
		const auto c = math::cos( radian );
		const auto s = math::sin( radian );

		return mat3<Type>(
			c, -s, 0,
			s, c, 0,
			0, 0, 1
		);
	}

	template <typename V = Type>
	static constexpr auto translate( const vec3<V>& vector ) noexcept {
		return mat3<Type>(
			1, 0, 0,
			0, 1, 0,
			vector.x, vector.y, vector.z
		);
	}

	constexpr mat3() noexcept : abc( { 1, 0, 0 } ), def( { 0, 1, 0 } ), ghi( { 0, 0, 1 } ) {}

	template <typename M>
	constexpr mat3( const mat3<M>& other ) noexcept : abc( other.abc ), def( other.def ), ghi( other.ghi ) {}

	template <typename S>
	constexpr mat3( S scalar ) noexcept : abc( { scalar, 0, 0 } ), def( { 0, scalar, 0 } ), ghi( { 0, 0, scalar } ) {}

	template <typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>
	constexpr mat3( A a, B b, C c, D d, E e, F f, G g, H h, I i ) noexcept : 
		abc( { a, b, c } ),
		def( { d, e, f } ),
		ghi( { g, h, i } ) {}

	template <typename V0, typename V1, typename V2>
	constexpr mat3( const vec3<V0>& v0, const vec3<V1>& v1, const vec3<V2>& v2 ) noexcept : 
		abc( v0 ),
		def( v1 ),
		ghi( v1 ) {}

	constexpr auto& operator []( size_type i ) noexcept {
		assert( i >= 0 && i < 3 );

		switch ( i ) {
		default:
		case 0:
			return abc;
		case 1:
			return def;
		case 2:
			return ghi;
		}
	}

	constexpr const auto& operator []( size_type i ) const noexcept {
		assert( i >= 0 && i < 3 );

		switch ( i ) {
		default:
		case 0:
			return abc;
		case 1:
			return def;
		case 2:
			return ghi;
		}
	}

	template <typename OType>
	constexpr auto& operator =( const mat3<OType>& other ) noexcept {
		abc = other.abc;
		def = other.def;
		ghi = other.ghi;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( OType scalar ) noexcept {
		abc += scalar;
		def += scalar;
		ghi += scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator +=( const mat3<OType>& other ) noexcept {
		abc += other.abc;
		def += other.def;
		ghi += other.ghi;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( OType scalar ) noexcept {
		abc -= scalar;
		def -= scalar;
		ghi -= scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator -=( const mat3<OType>& other ) noexcept {
		abc -= other.abc;
		def -= other.def;
		ghi -= other.ghi;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator *=( OType scalar ) noexcept {
		abc *= scalar;
		def *= scalar;
		ghi *= scalar;
		return *this;
	}

	template <typename OType>
	constexpr auto& operator /=( OType scalar ) noexcept {
		abc /= scalar;
		def /= scalar;
		ghi /= scalar;
		return *this;
	}

	constexpr auto& operator ++() noexcept {
		++abc;
		++def;
		++ghi;
		return *this;
	}

	constexpr auto& operator --() noexcept {
		--abc;
		--def;
		--ghi;
		return *this;
	}

	constexpr auto& operator ++( int ) noexcept {
		const auto r = *this;
		++abc;
		++def;
		++ghi;
		return r;
	}

	constexpr auto& operator --( int ) noexcept {
		const auto r = *this;
		--abc;
		--def;
		--ghi;
		return r;
	}
};

template <typename OType>
constexpr const auto& operator +( const mat3<OType>& m ) noexcept {
	return m;
}

template <typename OType>
constexpr auto operator -( const mat3<OType>& m ) noexcept {
	return mat3<OType>( -m.abc, -m.def, -m.ghi );
}

template <typename OType, typename S>
constexpr auto operator +( const mat3<OType>& m, S s ) noexcept {
	return mat3<OType>( m.abc + s, m.def + s, m.ghi + s );
}

template <typename AT, typename BT>
constexpr auto operator +( const mat3<AT>& a, const mat3<BT>& b ) noexcept {
	return mat3<AT>( a.abc + b.abc, a.def + b.def, a.ghi + b.ghi );
}

template <typename OType, typename S>
constexpr auto operator -( const mat3<OType>& m, S s ) noexcept {
	return mat3<OType>( m.abc - s, m.def - s, m.ghi - s );
}

template <typename AT, typename BT>
constexpr auto operator -( const mat3<AT>& a, const mat3<BT>& b ) noexcept {
	return mat3<AT>( a.abc - b.abc, a.def - b.def, a.ghi - b.ghi );
}

template <typename OType, typename S>
constexpr auto operator *( const mat3<OType>& m, S s ) noexcept {
	return mat3<OType>( m.abc * s, m.def * s, m.ghi * s );
}

template <typename S, typename OType>
constexpr auto operator *( S s, const mat3<OType>& m ) noexcept {
	return mat3<OType>( m.abc * s, m.def * s, m.ghi * s );
}

template <typename OType, typename VType>
constexpr auto operator *( const mat3<OType>& m, const vec3<VType>& v ) noexcept {
	return vec3<VType>(
		m.abc.x * v.x + m.def.x * v.y + m.ghi.x * v.z,
		m.abc.y * v.x + m.def.y * v.y + m.ghi.y * v.z,
		m.abc.z * v.x + m.def.z * v.y + m.ghi.z * v.z);
}

template <typename OType, typename VType>
constexpr auto operator *( const vec3<VType>& v, const mat3<OType>& m ) noexcept {
	return vec3<VType>(
		v.x * m.abc.x + v.y * m.abc.y + v.z * m.abc.z,
		v.x * m.def.x + v.y * m.def.y + v.z * m.def.z,
		v.x * m.ghi.x + v.y * m.ghi.y + v.z * m.ghi.z);
}

template <typename AT, typename BT>
constexpr auto operator *( const mat3<AT>& m1, const mat3<BT>& m2 ) noexcept {
	return mat3<AT>(
		m1.abc.x * m2.abc.x + m1.def.x * m2.abc.y + m1.ghi.x * m2.abc.z,
		m1.abc.y * m2.abc.x + m1.def.y * m2.abc.y + m1.ghi.y * m2.abc.z,
		m1.abc.z * m2.abc.x + m1.def.z * m2.abc.y + m1.ghi.z * m2.abc.z,
		m1.abc.x * m2.def.x + m1.def.x * m2.def.y + m1.ghi.x * m2.def.z,
		m1.abc.y * m2.def.x + m1.def.y * m2.def.y + m1.ghi.y * m2.def.z,
		m1.abc.z * m2.def.x + m1.def.z * m2.def.y + m1.ghi.z * m2.def.z,
		m1.abc.x * m2.ghi.x + m1.def.x * m2.ghi.y + m1.ghi.x * m2.ghi.z,
		m1.abc.y * m2.ghi.x + m1.def.y * m2.ghi.y + m1.ghi.y * m2.ghi.z,
		m1.abc.z * m2.ghi.x + m1.def.z * m2.ghi.y + m1.ghi.z * m2.ghi.z);
}

template <typename OType, typename S>
constexpr auto operator /( const mat3<OType>& m, S s ) noexcept {
	return mat3<OType>( m.abc / s, m.def / s, m.ghi / s );
}

template <typename S, typename OType>
constexpr auto operator /( S s, const mat3<OType>& m ) noexcept {
	return mat3<OType>( s / m.abc, s / m.def, s / m.ghi );
}

template <typename AT, typename BT>
constexpr auto operator ==( const mat3<AT>& m1, const mat3<BT>& m2 ) noexcept {
	return m1.abc == m2.abc && m1.def == m2.def && m1.ghi == m2.ghi;
}

template <typename AT, typename BT>
constexpr auto operator !=( const mat3<AT>& m1, const mat3<BT>& m2 ) noexcept {
	return !( m1 == m2 );
}

} // gba

#endif // define GBAXX_MAT3_HPP
