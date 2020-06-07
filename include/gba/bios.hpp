#ifndef GBAXX_BIOS_HPP
#define GBAXX_BIOS_HPP

#include <cassert>
#include <tuple>
#include <type_traits>

#include <gba/fixed_point.hpp>
#include <gba/int.hpp>
#include <gba/interrupt.hpp>
#include <gba/int_type.hpp>

/// @defgroup bios BIOS
/// @brief Various functions implemented in the GBA BIOS

namespace gba {
namespace bios {

/// @defgroup bios_reset Reset functions
/// @ingroup bios
/// @brief Functions for resetting the software and clearing memory

/// @ingroup bios_reset
/// @brief Reinitialises the system
[[noreturn]]
inline void soft_reset() noexcept {
#if defined( __thumb__ )
	__asm__ volatile (
		"swi %0\n\t"
			: : "g"( 0x0 )
	);
#else
	__asm__ volatile (
		"swi %0 << 16\n\t"
			: : "g"( 0x0 )
	);
#endif
}

/// @ingroup bios_reset
/// @brief Bit flags for gba::bios::register_ram_reset()
struct reset_flags {
	bool	ewram : 1,
			iwram : 1,
			palette : 1,
			vram : 1,
			oam : 1,
			serial_io : 1,
			sound : 1,
			registers : 1; //!< Resets all registers, excluding Serial IO and Sound
};

/// @ingroup bios_reset
/// @brief Resets the registers or RAM specified in the given flags
/// @param flags Bit field of registers or RAM to be reset
[[gnu::naked]]
inline void register_ram_reset( reset_flags flags ) noexcept {
#if defined( __thumb__ )
	__asm__ volatile (
		"swi %0\n\t"
		"bx lr\n\t"
			: : "g"( 0x1 )
	);
#else
	__asm__ volatile (
		"swi %0 << 16\n\t"
		"bx lr\n\t"
			: : "g"( 0x1 )
	);
#endif
}

/// @defgroup bios_halt Halt functions
/// @ingroup bios
/// @brief Functions for sleeping or halting the CPU until interupt flags are raised.

/// @ingroup bios_halt
/// @brief Sets the CPU into low-power mode until any enabled interrupt is raised
///
/// gba::bios::halt ignores the gba::io::interrupt_master_enable register and only watches the
/// gba::io::interrupt_mask_enable and gba::io::interrupt_flags for a raised interrupt
inline void halt() noexcept {
#if defined( __thumb__ )
	__asm__ volatile (
		"swi %0\n\t"
			: : "g"( 0x2 )
		);
#else
	__asm__ volatile (
		"swi %0 << 16\n\t"
			: : "g"( 0x2 )
		);
#endif
}

/// @ingroup bios_halt
/// @brief Sets the CPU into low-power mode until any _supported_ enabled interrupt is raised
///
/// The supported interrupts are:
/// * gba::interrupt::serial_communication
/// * gba::interrupt::keypad
/// * gba::interrupt::game_pak
inline void stop() noexcept {
#if defined( __thumb__ )
	__asm__ volatile (
		"swi %0\n\t"
			: : "g"( 0x3 )
		);
#else
	__asm__ volatile (
		"swi %0 << 16\n\t"
			: : "g"( 0x3 )
		);
#endif
}

/// @ingroup bios_halt
/// @brief Waits in halt state until any of the given gba::interrupt flags are raised
///
/// This forces the gba::io::interrupt_master_enable to true
/// @param clearFlags Clear any previously set interrupt flags
/// @param flags Interrupt flags to wait on
[[gnu::naked]]
inline void intr_wait( bool clearFlags, interrupt flags ) noexcept {
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

/// @ingroup bios_halt
/// @brief Calls gba::bios::intr_wait() with the gba::interrupt::vblank flag set
inline void vblank_intr_wait() noexcept {
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

/// @defgroup bios_math Math functions
/// @ingroup bios
/// @brief Mathematical functions

/// @ingroup bios_math
/// @brief Signed integer division
///
/// This has no protection for divide-by-zero and will hang
/// @param a numerator
/// @param b denominator
/// @return std::tuple containing the results of: `a / b`, `a % b` and `std::abs( a / b )`
inline std::tuple<int32, int32, uint32> div( volatile int32 a, volatile int32 b ) noexcept {
	assert( b != 0 );

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

/// @ingroup bios_math
/// @brief Functionally equivalent of bios::div(), but the arguments are swapped
/// @param a denominator
/// @param b numerator
/// @return std::tuple containing the results of: `b / a`, `b % a` and `std::abs( b / a )`
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

/// @ingroup bios_math
/// @brief Returns the integer square root of x
/// @param x integer
/// @return square root of x
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

/// @ingroup bios_math
/// @brief Returns the fixed-point square root of x
/// @param x gba::fixed_point
/// @return square root of x
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

		/// @brief Start CPU set
		/// @param src source address
		/// @param dst destination address
		/// @return *this reference
		template <typename Source, typename Dest>
		auto& invoke( const Source * src, Dest * dst ) const noexcept {
			cpu_set( src, dst, m_setting );
			return *this;
		}

		/// @brief Start CPU set
		/// @param src source address
		/// @param dst destination integer address
		/// @return *this reference
		template <typename Source>
		auto& invoke( const Source * src, uintptr dst ) const noexcept {
			cpu_set( src, dst, m_setting );
			return *this;
		}

		/// @brief Calls cpu_set_shared::invoke()
		/// @param src source address
		/// @param dst destination integer address
		/// @return *this reference
		template <typename Source, typename Dest>
		auto& operator()( const Source * src, Dest * dst ) const noexcept {
			return invoke( src, dst );
		}

		/// @brief Calls cpu_set_shared::invoke()
		/// @param src source address
		/// @param dst destination integer address
		/// @return *this reference
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

		/// @brief Start CPU fast set
		/// @param src source address
		/// @param dst destination integer address
		/// @return *this reference
		template <typename Source, typename Dest>
		auto& invoke( const Source * src, Dest * dst ) const noexcept {
			detail::cpu_fast_set( src, dst, m_setting );
			return *this;
		}

		/// @brief Start CPU fast set
		/// @param src source address
		/// @param dst destination integer address
		/// @return *this reference
		template <typename Source>
		auto& invoke( const Source * src, uintptr dst ) const noexcept {
			detail::cpu_fast_set( src, dst, m_setting );
			return *this;
		}

		/// @brief Calls cpu_fast_set_shared::invoke()
		/// @param src source address
		/// @param dst destination integer address
		/// @return *this reference
		template <typename Source, typename Dest>
		auto& operator()( const Source * src, Dest * dst ) const noexcept {
			return invoke( src, dst );
		}

		/// @brief Calls cpu_fast_set_shared::invoke()
		/// @param src source address
		/// @param dst destination integer address
		/// @return *this reference
		template <typename Source>
		auto& operator()( const Source * src, uintptr dst ) const noexcept {
			return invoke( src, dst );
		}

	};

} // detail

/// @defgroup bios_memcpy Memory copy/set functions
/// @ingroup bios
/// @brief These are similar to, but not equivalent to std::memcpy() and std::memset()
///
/// Copy example:
/// ```cpp
/// char source[] = "today is a good day", dest[8];
/// bios::cpu_copy32(2).invoke(source, dest); // Copy two 32bit words from source into dest
///
/// // dest[] == ['t', 'o', 'd', 'a', 'y', ' ', 'i', 's']
/// ```
/// Set example:
/// ```cpp
/// int a[24];
/// int b = 0xc0ffee;
/// bios::cpu_set32(24).invoke(&b, a); // Fill a[24] with the value 0xc0ffee
///
/// // a[] == [0xc0ffee, 0xc0ffee, 0xc0ffee, ..., 0xc0ffee]
/// ```

/// @ingroup bios_memcpy
/// @brief copies wordcount * int16 values from source to destination
class cpu_copy16 : public detail::cpu_set_shared {
public:
	constexpr cpu_copy16( uint32 wordcount ) noexcept : detail::cpu_set_shared( { wordcount, false, false } ) {}
};

/// @ingroup bios_memcpy
/// @brief copies wordcount * int32 values from source to destination
class cpu_copy32 : public detail::cpu_set_shared {
public:
	constexpr cpu_copy32( uint32 wordcount ) noexcept : detail::cpu_set_shared( { wordcount, false, true } ) {}
};

/// @ingroup bios_memcpy
/// @brief copies wordcount * int32 values from source to destination in groups of 8
///
/// If wordcount is not a multiple of 8 then it is round up to the next multiple of 8
class cpu_copy32x8 : public detail::cpu_fast_set_shared {
public:
	constexpr cpu_copy32x8( uint32 wordcount ) noexcept : detail::cpu_fast_set_shared( { wordcount, false, true } ) {}
};

/// @ingroup bios_memcpy
/// @brief sets wordcount * int16 values in destination to the int16 value stored in source
class cpu_set16 : public detail::cpu_set_shared {
public:
	constexpr cpu_set16( uint32 wordcount ) noexcept : detail::cpu_set_shared( { wordcount, true, false } ) {}
};

/// @ingroup bios_memcpy
/// @brief sets wordcount * int32 values in destination to the int32 value stored in source
class cpu_set32 : public detail::cpu_set_shared {
public:
	constexpr cpu_set32( uint32 wordcount ) noexcept : detail::cpu_set_shared( { wordcount, true, true } ) {}
};

/// @ingroup bios_memcpy
/// @brief sets wordcount * int32 values in destination to the int32 value stored in source in groups of 8
///
/// If wordcount is not a multiple of 8 then it is round up to the next multiple of 8
class cpu_set32x8 : public detail::cpu_fast_set_shared {
public:
	constexpr cpu_set32x8( uint32 wordcount ) noexcept : detail::cpu_fast_set_shared( { wordcount, true, true } ) {}
};

namespace undocumented {

	/// @defgroup bios_undocumented Undocumented
	/// @ingroup bios
	/// @brief Various functions implemented, but not considered "documented"

	/// @ingroup bios_undocumented
	/// @brief Reboots the device
	[[noreturn]]
	inline void hard_reset() noexcept {
#if defined( __thumb__ )
		__asm__ volatile (
			"swi %0\n\t"
			: : "g"( 0x26 )
			);
#else
		__asm__ volatile (
			"swi %0 << 16\n\t"
			: : "g"( 0x26 )
			);
#endif
	}

	/// @ingroup bios_undocumented
	/// @brief Calculates the checksum of the BIOS ROM
	///
	/// System checksums:
	/// AGB & AGS  | NDS & 3DS
	/// -----------|-----------
	/// 0xBAAE187F | 0xBAAE1880
	/// These values are calculated by summing the BIOS as 4096 32bit integers
	/// @return uint32 checksum
	[[gnu::naked]]
	inline uint32 get_bios_checksum() noexcept {
#if defined( __thumb__ )
		__asm__ volatile (
			"swi %0\n\t"
			"bx lr\n\t"
			: : "g"( 0x26 ) : "r0"
			);
#else
		__asm__ volatile (
			"swi %0 << 16\n\t"
			"bx lr\n\t"
			: : "g"( 0x26 ) : "r0"
			);
#endif
	}

} // undocumented

} // bios
} // gba

#endif // define GBAXX_BIOS_HPP
