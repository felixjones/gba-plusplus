#ifndef GBAXX_BOOL_TYPE_HPP
#define GBAXX_BOOL_TYPE_HPP

#include <limits>
#include <type_traits>

#include <gba/int_type.hpp>

namespace gba {
namespace detail {

    template <unsigned int Size>
    class boolean_padding {
    private:
        char    m_padding[Size];
    };

    class boolean_zero_padding {};

} // detail

template <unsigned int BitSize, unsigned int BitIndex = 0>
class bool_type : std::conditional<( BitIndex ) / 8 == 0, detail::boolean_zero_padding, detail::boolean_padding<BitIndex / 8>>::type {
    static_assert( BitIndex < BitSize, "bool_type BitIndex must be less than BitSize" );

    using uint_type = typename uint_type<BitSize - ( ( BitIndex / 8 ) * 8 )>::type;

    static constexpr auto spare_head_bits = BitIndex % 8;

    struct field_type {
        bool    : spare_head_bits;
        bool    value : 1;
    };

    union union_type {
        field_type  field;
        uint_type   raw;
    };

public:
    constexpr bool_type() noexcept : m_data { false } {}

    constexpr bool_type( const bool value ) noexcept : m_data { value } {}

    constexpr auto& operator=( const bool value ) noexcept {
        set_value( value );
        return *this;
    }

    constexpr operator auto() const noexcept {
        return get_value();
    }

    constexpr auto operator!() const noexcept {
        return !get_value();
    }

    constexpr auto operator~() const noexcept {
        return ~get_value();
    }

    constexpr auto operator-() const noexcept {
        return -get_value();
    }

    constexpr auto operator+() const noexcept {
        return +get_value();
    }

	constexpr auto& operator+=( const bool value ) noexcept {
		set_value( get_value() + value );
		return *this;
	}

	constexpr auto& operator-=( const bool value ) noexcept {
		set_value( get_value() - value );
		return *this;
	}

	constexpr auto& operator*=( const bool value ) noexcept {
		set_value( get_value() * value );
		return *this;
	}

	constexpr auto& operator/=( const bool value ) noexcept {
		set_value( get_value() / value );
		return *this;
	}

	constexpr auto& operator%=( const bool value ) noexcept {
		set_value( get_value() % value );
		return *this;
	}

	constexpr auto& operator>>=( const unsigned int value ) noexcept {
		set_value( get_value() >> value );
		return *this;
	}

	constexpr auto& operator<<=( const unsigned int value ) noexcept {
		set_value( get_value() << value );
		return *this;
	}

	constexpr auto& operator|=( const bool value ) noexcept {
		set_value( get_value() | value );
		return *this;
	}

	constexpr auto& operator&=( const bool value ) noexcept {
		set_value( get_value() & value );
		return *this;
	}

	constexpr auto& operator^=( const bool value ) noexcept {
		set_value( get_value() ^ value );
		return *this;
	}

	constexpr auto& operator|=( const bool_type& value ) noexcept {
		m_data.raw |= value.m_data.raw;
		return *this;
	}

	constexpr auto& operator&=( const bool_type& value ) noexcept {
		m_data.raw &= value.m_data.raw;
		return *this;
	}

	constexpr auto& operator^=( const bool_type& value ) noexcept {
		m_data.raw ^= value.m_data.raw;
		return *this;
	}

private:
    constexpr bool get_value() const noexcept {
        return m_data.field.value;
    }

    constexpr void set_value( bool value ) noexcept {
        m_data.field.value = value;
    }

    union_type  m_data;

};

} // gba

template <unsigned int BitSize, unsigned int BitIndex>
struct std::numeric_limits<gba::bool_type<BitSize, BitIndex>> : public std::numeric_limits<bool> {};

#endif // GBAXX_BOOL_TYPE_HPP
