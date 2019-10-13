#ifndef GBAXX_IO_REG_HPP
#define GBAXX_IO_REG_HPP

#include <gba/int_type.hpp>

namespace gba {
namespace io {

// Register access class
// Optimised to remove std::memcpy calls
template <typename Type>
class reg {
public:
	using uint_type = typename uint_sized_type<sizeof( Type )>::type;

	Type read() const {
		const auto value = m_data;
		return *( const Type * )&value;
	}

	void write( const Type& value ) {
		m_data = *( const uint_type * )&value;
	}

private:
	volatile uint_type	m_data;

};

} // io
} // gba

#endif // define GBAXX_IO_REG_HPP