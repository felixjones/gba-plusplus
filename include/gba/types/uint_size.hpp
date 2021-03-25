#ifndef GBAXX_TYPES_UINT_SIZE_HPP
#define GBAXX_TYPES_UINT_SIZE_HPP

#include <gba/types/int_type.hpp>

namespace gba {

template <unsigned int Bits>
class uint_size {
    static_assert( Bits > 0, "uint_size Bits cannot be zero" );

    using data_type = typename uint_type<Bits>::type;
public:
    constexpr uint_size() noexcept = default;
    constexpr uint_size( uint32 data ) noexcept : m_data { static_cast<data_type>( data - 1 ) } {}

    [[nodiscard]]
    constexpr operator uint32() const noexcept {
        return m_data + 1;
    }

    constexpr uint_size& operator =( const uint32 data ) noexcept {
        m_data = data - 1;
        return *this;
    }

private:
    data_type m_data;
};

using uint_size8 = uint_size<8>;
using uint_size16 = uint_size<16>;
using uint_size32 = uint_size<32>;

} // gba

#endif // define GBAXX_TYPES_UINT_SIZE_HPP
