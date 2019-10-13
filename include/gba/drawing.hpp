#ifndef GBAXX_DRAWING_HPP
#define GBAXX_DRAWING_HPP

#include <gba/int.hpp>
#include <gba/color.hpp>

namespace gba {
namespace drawing {

/*
auto surface = gba::gfx::surface_mode<3>();
auto renderer = gba::gfx::renderer( surface ); // Type of surface will give you type of renderer
renderer.set_pixel( 0, 0, 2 );
*/

class surface {
public:

protected:
	uint16	m_width;
	uint16	m_height;

};

class graphics {
public:
	constexpr graphics() {}


};




// Base graphics class
// No specialisation
class graphics {
public:
	uint8 width() const {
		return m_width;
	}

	uint8 height() const {
		return m_height;
	}

protected:
	constexpr graphics( uint8 w, uint8 h ) : m_width( w ), m_height( h ) {}

private:
	uint8	m_width;
	uint8	m_height;

};

class graphics_index8 : public graphics {
public:
	template <typename Type = void>
	graphics_index8( Type * addr, uint8 w, uint8 h, uint16 stride ) : graphics( w, h ), m_addr( reinterpret_cast<uint8 *>( addr ) ), m_stride( stride ) {}

	void set_pixel( uint8 x, uint8 y, uint8 i ) {
		m_addr[y * m_stride + x] = i;
	}

private:
	uint16	m_stride;
	uint8 *	m_addr;

};


class graphics_bgr15 {
public:
	graphics_bgr15( uintptr addr, uint8 w, uint8 h ) : m_data( reinterpret_cast<uint16 *>( addr ) ), m_width( w ), m_height( h ) {}

	void set_pixel( uint8 x, uint8 y, color c ) {
		m_data[m_width * y + x] = c.to_uint16();
	}

private:
	uint16 *	m_data;
	uint8		m_width;
	uint8		m_height;

};

template <unsigned Mode>
constexpr const auto graphics_mode() {
	if constexpr ( Mode == 3 ) {
		return graphics_bgr15( 0x6000000, 240, 160 );
	}
	// TODO : Return a constexpr graphics instance for a particular mode
}

} // drawing
} // gba

#endif // define GBAXX_DRAWING_HPP