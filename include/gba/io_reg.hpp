#ifndef GBAXX_IO_REG_HPP
#define GBAXX_IO_REG_HPP

#include <gba/bit_cast.hpp>
#include <gba/int_type.hpp>

namespace gba {
namespace io {

// Register access class
template <typename Type>
class reg {
public:
	using uint_type = typename uint_sized_type<sizeof( Type )>::type;

	Type read() const {
		const auto data = m_data;
		return gba::bit_cast<Type>( data );
	}

	void write( const Type& value ) {
		uint_type data = 0;
		std::memcpy( &data, &value, sizeof( value ) );
		m_data = data;
	}

private:
	volatile uint_type	m_data;

};

} // io
} // gba

#endif // define GBAXX_IO_REG_HPP