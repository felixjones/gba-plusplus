#ifndef GBAXX_MEMMAP_HPP
#define GBAXX_MEMMAP_HPP

#include <type_traits>
#include <cstring>

#include <gba/int_type.hpp>

namespace gba {

template <typename Type, unsigned Address>
class memmap {
	static_assert( sizeof( Type ) <= 8, "Type is too big." );
public:
	using type = Type;
	static const auto address = Address;
};

// Read only memory mapped
template <typename Type, unsigned Address, typename Fundamental = void>
class imemmap;

template <typename Type, unsigned Address>
class imemmap<Type, Address, typename std::enable_if<std::is_fundamental<Type>::value>::type> : public virtual memmap<Type, Address> {
private:
	using uint_type = typename uint_sized_type<sizeof( Type )>::type;

public:
	static Type read() noexcept {
		return *( volatile const Type * )Address;
	}
};

template <typename Type, unsigned Address>
class imemmap<Type, Address, typename std::enable_if<!std::is_fundamental<Type>::value>::type> : public virtual memmap<Type, Address> {
private:
	using uint_type = typename uint_sized_type<sizeof( Type )>::type;

public:
	static Type read() noexcept {
		const uint_type data = *( volatile const uint_type * )Address;
		Type value {};
		std::memcpy( &value, &data, sizeof( Type ) );
		return value;
	}
};

// Write only memory mapped
template <typename Type, unsigned Address, typename Fundamental = void>
class omemmap;

template <typename Type, unsigned Address>
class omemmap<Type, Address, typename std::enable_if<std::is_fundamental<Type>::value && !std::is_const<Type>::value>::type> : public virtual memmap<Type, Address> {
private:
	using uint_type = typename uint_sized_type<sizeof( Type )>::type;

public:
	static void write( const Type& value ) noexcept {
		*( volatile Type * )Address = value;
	}
};

template <typename Type, unsigned Address>
class omemmap<Type, Address, typename std::enable_if<!std::is_fundamental<Type>::value && !std::is_const<Type>::value>::type> : public virtual memmap<Type, Address> {
private:
	using uint_type = typename uint_sized_type<sizeof( Type )>::type;

public:
	static void write( const Type& value ) noexcept {
		uint_type data {};
		std::memcpy( &data, &value, sizeof( Type ) );
		*( volatile uint_type * )Address = data;
	}
};

template <typename Type, unsigned Address>
class iomemmap : public imemmap<Type, Address>, public omemmap<Type, Address> {};

}

#endif // define GBAXX_MEMMAP_HPP
