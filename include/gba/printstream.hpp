#ifndef GBAXX_PRINTSTREAM_HPP
#define GBAXX_PRINTSTREAM_HPP

#include <algorithm>
#include <cstring>
#include <sstream>

#include <gba/int.hpp>
#include <gba/memmap.hpp>

namespace gba {
namespace mgba {
namespace detail {

	inline uint32 ref_count = 0;

	inline bool open() noexcept {
		if ( ref_count == 0 ) {
			using debug_enable = iomemmap<uint16, 0x4FFF780>;

			debug_enable::write( 0xC0DE );
			if ( debug_enable::read() != 0x1DEA ) {
				return false;
			}
		}

		++ref_count;
		return true;
	}

	inline void close() noexcept {
		--ref_count;

		if ( ref_count == 0 ) {
			using debug_enable = omemmap<uint16, 0x4FFF780>;

			debug_enable::write( 0x0000 );
		}
	}

	inline int puts( int level, const std::string& str ) noexcept {
		using debug_flags = omemmap<uint16, 0x4FFF700>;
		const auto debug_string = reinterpret_cast<char *>( 0x4FFF600 );

		const auto length = std::min( static_cast<int>( str.length() ), 0x100 );
		std::memcpy( debug_string, str.c_str(), length );
		debug_flags::write( level | 0x100 );
		return length;
	}

} // detail

enum log_type {
	log_fatal = 0,
	log_error = 1,
	log_warn = 2,
	log_info = 3,
	log_debug = 4
};

class streambuf : public std::stringbuf {
public:
	streambuf( log_type level ) : m_level( level ) {
#if defined( __EXCEPTIONS )
		if ( detail::open() == false ) {
			throw;
		}
#else
		m_open = detail::open();
#endif
	}

	virtual ~streambuf() noexcept {
#if !defined( __EXCEPTIONS )
		if ( !m_open ) {
			return;
		}
#endif

		detail::close();
	}

	virtual int sync() {
#if !defined( __EXCEPTIONS )
		if ( !m_open ) {
			return 0;
		}
#endif

		const auto result = detail::puts( m_level, str() );
		str( {} ); // Clear buffer
		return result;
	}

protected:
	const log_type	m_level;

#if !defined( __EXCEPTIONS )
	bool	m_open;
#endif

};

} // mgba
} // gba

#endif // define GBAXX_DEBUG_PRINTSTREAM_HPP
