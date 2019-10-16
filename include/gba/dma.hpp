#ifndef GBAXX_DMA_HPP
#define GBAXX_DMA_HPP

#include <cstring>

#include <gba/int.hpp>
#include <gba/io_reg.hpp>

namespace gba {
namespace dma {

enum addr_op {
	op_increment = 0x0,
	op_decrement = 0x1,
	op_fixed = 0x2,
	op_increment_reload = 0x3
};

struct [[gnu::packed]] control {

	uint8	: 5;
	addr_op	destination_op : 2;
	addr_op	source_op : 2;
	bool	repeat : 1,
			long_word : 1,
			dreq_stop : 1;
	uint8	start_mode : 2;
	bool	emit_irq_end : 1,
			enabled : 1;

};

} // dma

namespace io {

namespace dma {

class channel {
public:
	template <typename Type>
	channel& source( const Type * src ) {
		uintptr value;
		std::memcpy( &value, &src, sizeof( value ) );
		m_source.write( value );
		return *this;
	}

	template <typename Type>
	channel& destination( Type * dst ) {
		uintptr value;
		std::memcpy( &value, &dst, sizeof( value ) );
		m_destination.write( value );
		return *this;
	}

	channel& words( uint16 value ) {
		m_wordCount.write( value );
		return *this;
	}

	channel& control( const gba::dma::control& value ) {
		m_control.write( value );
		return *this;
	}

	gba::dma::control control() const {
		return m_control.read();
	}

private:
	reg<uintptr>			m_source;
	reg<uintptr>			m_destination;
	reg<uint16>				m_wordCount;
	reg<gba::dma::control>	m_control;

};

static channel& channel0 = *reinterpret_cast<channel *>( 0x40000B0 );
static channel& channel1 = *reinterpret_cast<channel *>( 0x40000BC );
static channel& channel2 = *reinterpret_cast<channel *>( 0x40000C8 );
static channel& channel3 = *reinterpret_cast<channel *>( 0x40000D4 );
	
} // dma

} // io
} // gba

#endif // define GBAXX_DMA_HPP