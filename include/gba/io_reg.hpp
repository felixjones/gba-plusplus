#ifndef GBAXX_IO_REG_HPP
#define GBAXX_IO_REG_HPP

#include <cstring>

namespace gba {
namespace io {

template <typename Type>
class reg {
public:

	Type read() const {
		Type b;
		std::memcpy( &b, ( const void * )&m_data, sizeof( m_data ) );
		return b;
	}

	void write( const Type& b ) {
		std::memcpy( ( void * )&m_data, &b, sizeof( b ) );
	}

private:
	volatile Type	m_data;

};

} // io
} // gba

#endif // define GBAXX_IO_REG_HPP