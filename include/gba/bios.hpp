#ifndef GBAXX_BIOS_HPP
#define GBAXX_BIOS_HPP

#include <tuple>
#include <type_traits>

#include <gba/fixed_point.hpp>
#include <gba/int.hpp>
#include <gba/int_type.hpp>

namespace gba {
namespace bios {

inline void vblank_intr_wait() {
#if defined( __thumb__ )
	__asm__ volatile (
		"swi %0\n\t"
			: : "g"( 0x5 ) : "r0", "r1"
	);
#else
	__asm__ volatile (
		"swi %0 << 16\n\t"
			: : "g"( 0x5 ) : "r0", "r1"
	);
#endif
}

inline std::tuple<int32, int32, uint32> div( volatile int32 a, volatile int32 b ) noexcept {
	volatile uint32 c;

#if defined( __thumb__ )
	__asm__ volatile (
		"mov r0, %4\n\t"
		"mov r1, %5\n\t"
		"swi %3\n\t"
		"mov %0, r0\n\t"
		"mov %1, r1\n\t"
		"mov %2, r3\n\t"
			: "=r"( a ), "=r"( b ), "=r"( c ) : "g"( 0x6 ), "r"( a ), "r"( b ) : "r0", "r1", "r3"
	);
#else
	__asm__ volatile (
		"mov r0, %4\n\t"
		"mov r1, %5\n\t"
		"swi %3 << 16\n\t"
		"mov %0, r0\n\t"
		"mov %1, r1\n\t"
		"mov %2, r3\n\t"
			: "=r"( a ), "=r"( b ), "=r"( c ) : "g"( 0x6 ), "r"( a ), "r"( b ) : "r0", "r1", "r3"
	);
#endif

	return std::make_tuple( a, b, c );
}

inline std::tuple<int32, int32, uint32> div_arm( volatile int32 a, volatile int32 b ) noexcept {
	volatile uint32 c;

#if defined( __thumb__ )
	__asm__ volatile (
		"mov r0, %5\n\t"
		"mov r1, %4\n\t"
		"swi %3\n\t"
		"mov %0, r0\n\t"
		"mov %1, r1\n\t"
		"mov %2, r3\n\t"
			: "=r"( a ), "=r"( b ), "=r"( c ) : "g"( 0x7 ), "r"( a ), "r"( b ) : "r0", "r1", "r3"
	);
#else
	__asm__ volatile (
		"mov r0, %5\n\t"
		"mov r1, %4\n\t"
		"swi %3 << 16\n\t"
		"mov %0, r0\n\t"
		"mov %1, r1\n\t"
		"mov %2, r3\n\t"
			: "=r"( a ), "=r"( b ), "=r"( c ) : "g"( 0x7 ), "r"( a ), "r"( b ) : "r0", "r1", "r3"
	);
#endif

	return std::make_tuple( a, b, c );
}

template <class T>
[[gnu::naked]]
inline auto sqrt( T x ) noexcept -> typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value, T>::type {
#if defined( __thumb__ )
	__asm__ volatile (
		"swi %0\n\t" 
		"bx lr\n\t"
			: : "g"( 0x8 ) : "r0"
	);
#else
	__asm__ volatile (
		"swi %0 << 16\n\t" 
		"bx lr\n\t"
			: : "g"( 0x8 ) : "r0"
	);
#endif
}

template <typename ReprType, unsigned ExpBits>
auto sqrt( const fixed_point<ReprType, ExpBits>& x ) noexcept {
	using exp_even_type = fixed_point<uint32, ExpBits - ( ExpBits % 2 )>;
	using exp_half_type = fixed_point<uint32, exp_even_type::exponent / 2>;

	const auto resultData = sqrt( exp_even_type( x ).data() );
	const auto resultFixed = exp_half_type::from_data( resultData );
	return fixed_point<ReprType, ExpBits>( resultFixed );
}

namespace detail {

	struct length_mode {
		uint32	word_count : 21,
				: 3;
		bool	fixed_source_address : 1,
				: 1,
				datasize : 1;
	};

	template <typename Source, typename Dest>
	[[gnu::naked]]
	void cpu_fast_set( const Source * src, Dest * dst, length_mode lengthMode ) {
#if defined( __thumb__ )
		__asm__ volatile (
			"swi %0\n\t" 
			"bx lr\n\t"
				: : "g"( 0xC )
		);
#else
		__asm__ volatile (
			"swi %0 << 16\n\t" 
			"bx lr\n\t"
				: : "g"( 0xC )
		);
#endif
	}

	template <typename Source>
	[[gnu::naked]]
	void cpu_fast_set( const Source * src, uintptr dst, length_mode lengthMode ) {
#if defined( __thumb__ )
		__asm__ volatile (
			"swi %0\n\t" 
			"bx lr\n\t"
				: : "g"( 0xC )
		);
#else
		__asm__ volatile (
			"swi %0 << 16\n\t" 
			"bx lr\n\t"
				: : "g"( 0xC )
		);
#endif
	}

	template <typename Source, typename Dest>
	[[gnu::naked]]
	void cpu_set( const Source * src, Dest * dst, length_mode lengthMode ) {
#if defined( __thumb__ )
		__asm__ volatile (
			"swi %0\n\t" 
			"bx lr\n\t"
				: : "g"( 0xB )
		);
#else
		__asm__ volatile (
			"swi %0 << 16\n\t" 
			"bx lr\n\t"
				: : "g"( 0xB )
		);
#endif
	}

	template <typename Source>
	[[gnu::naked]]
	void cpu_set( const Source * src, uintptr dst, length_mode lengthMode ) {
#if defined( __thumb__ )
		__asm__ volatile (
			"swi %0\n\t" 
			"bx lr\n\t"
				: : "g"( 0xB )
		);
#else
		__asm__ volatile (
			"swi %0 << 16\n\t" 
			"bx lr\n\t"
				: : "g"( 0xB )
		);
#endif
	}

	class cpu_set_shared {
	public:
		constexpr cpu_set_shared( const length_mode& setting ) noexcept : m_setting( setting ) {}

		template <typename Source, typename Dest>
		auto& invoke( const Source * src, Dest * dst ) const noexcept {
			cpu_set( src, dst, m_setting );
			return *this;
		}

		template <typename Source>
		auto& invoke( const Source * src, uintptr dst ) const noexcept {
			cpu_set( src, dst, m_setting );
			return *this;
		}

		template <typename Source, typename Dest>
		auto& operator()( const Source * src, Dest * dst ) const noexcept {
			return invoke( src, dst );
		}

		template <typename Source>
		auto& operator()( const Source * src, uintptr dst ) const noexcept {
			return invoke( src, dst );
		}

	protected:
		const length_mode	m_setting;

	};

	class cpu_fast_set_shared : public detail::cpu_set_shared {
	public:
		constexpr cpu_fast_set_shared( const length_mode& setting ) noexcept : cpu_set_shared( setting ) {}

		template <typename Source, typename Dest>
		auto& invoke( const Source * src, Dest * dst ) const noexcept {
			detail::cpu_fast_set( src, dst, m_setting );
			return *this;
		}

		template <typename Source>
		auto& invoke( const Source * src, uintptr dst ) const noexcept {
			detail::cpu_fast_set( src, dst, m_setting );
			return *this;
		}

		template <typename Source, typename Dest>
		auto& operator()( const Source * src, Dest * dst ) const noexcept {
			return invoke( src, dst );
		}

		template <typename Source>
		auto& operator()( const Source * src, uintptr dst ) const noexcept {
			return invoke( src, dst );
		}

	};

} // detail

class cpu_copy16 : public detail::cpu_set_shared {
public:
	constexpr cpu_copy16( uint32 wordcount ) noexcept : detail::cpu_set_shared( { wordcount, false, false } ) {}
};

class cpu_copy32 : public detail::cpu_set_shared {
public:
	constexpr cpu_copy32( uint32 wordcount ) noexcept : detail::cpu_set_shared( { wordcount, false, true } ) {}
};

class cpu_copy32x8 : public detail::cpu_fast_set_shared {
public:
	constexpr cpu_copy32x8( uint32 wordcount ) noexcept : detail::cpu_fast_set_shared( { wordcount, false, true } ) {}
};

class cpu_set16 : public detail::cpu_set_shared {
public:
	constexpr cpu_set16( uint32 wordcount ) noexcept : detail::cpu_set_shared( { wordcount, true, false } ) {}
};

class cpu_set32 : public detail::cpu_set_shared {
public:
	constexpr cpu_set32( uint32 wordcount ) noexcept : detail::cpu_set_shared( { wordcount, true, true } ) {}
};

class cpu_set32x8 : public detail::cpu_fast_set_shared {
public:
	constexpr cpu_set32x8( uint32 wordcount ) noexcept : detail::cpu_fast_set_shared( { wordcount, true, true } ) {}
};

} // bios
} // gba

#endif // define GBAXX_BIOS_HPP
