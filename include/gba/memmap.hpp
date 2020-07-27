#ifndef GBAXX_MEMMAP_HPP
#define GBAXX_MEMMAP_HPP

#include <cstring>
#include <type_traits>

#include <gba/int_type.hpp>

namespace gba {
namespace detail {

	template <class Type>
	struct converts_to_uint {
		static constexpr bool value = sizeof( Type ) == 1 || sizeof( Type ) == 2 || sizeof( Type ) == 4;
	};

} // detail

template <typename Type, unsigned Address>
class memmap {
public:
	using type = Type;
	static constexpr auto address = Address;
};

// Read only memory mapped
template <typename Type, unsigned Address, typename Fundamental = void>
class imemmap;

template <typename Type, unsigned Address>
class imemmap<Type, Address, typename std::enable_if<detail::converts_to_uint<Type>::value && std::is_fundamental<Type>::value>::type> : public virtual memmap<Type, Address> {
private:
	using uint_type = typename uint_sized_type<sizeof( Type )>::type;

public:
	static Type read() noexcept {
		return *( volatile const Type * )Address;
	}
};

template <typename Type, unsigned Address>
class imemmap<Type, Address, typename std::enable_if<detail::converts_to_uint<Type>::value && !std::is_fundamental<Type>::value>::type> : public virtual memmap<Type, Address> {
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
class omemmap<Type, Address, typename std::enable_if<detail::converts_to_uint<Type>::value && std::is_fundamental<Type>::value>::type> : public virtual memmap<Type, Address> {
private:
	using uint_type = typename uint_sized_type<sizeof( Type )>::type;

public:
	static void write( const Type& value ) noexcept {
		*( volatile Type * )Address = value;
	}
};

template <typename Type, unsigned Address>
class omemmap<Type, Address, typename std::enable_if<detail::converts_to_uint<Type>::value && !std::is_fundamental<Type>::value && !std::is_const<Type>::value>::type> : public virtual memmap<Type, Address> {
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

} // gba

#endif // define GBAXX_MEMMAP_HPP
