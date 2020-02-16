#ifndef GBAXX_PACKED_PTR_HPP
#define GBAXX_PACKED_PTR_HPP

#include <gba/int.hpp>
#include <gba/bit_cast.hpp>

namespace gba {

template <class Type, unsigned Base, unsigned End, unsigned Alignment>
class packed_ptr {
public:
    constexpr static auto range = End - Base;
    constexpr static auto maximal = range / Alignment;
    constexpr static auto bits = ( 32 - __builtin_clz( maximal ) );

    static constexpr packed_ptr from( Type real ) {
        packed_ptr p;
        p.m_data = ( real / Alignment ) - Base;
        return p;
    }

    template <typename PtrType>
    static constexpr packed_ptr from( PtrType * address ) {
        packed_ptr p;
        p.m_data = ( bit_cast<Type>( address ) / Alignment ) - Base;
        return p;
    }

    constexpr Type value() const {
        return ( m_data * Alignment ) + Base;
    }

protected:
    using data_type = typename std::conditional<bits <= 8, std::int8_t, typename std::conditional<bits <= 16, std::int16_t, typename std::conditional<bits <= 32, std::int32_t, std::int64_t>::type>::type>::type;

    constexpr packed_ptr() : m_data( 0 ) {}

    data_type   m_data;

};

template <unsigned Base, unsigned End, unsigned Alignment = 4>
using packed_intptr = packed_ptr<intptr, Base, End, Alignment>;

template <unsigned Base, unsigned End, unsigned Alignment = 4>
using packed_uintptr = packed_ptr<uintptr, Base, End, Alignment>;

} // gba

#endif // define GBAXX_PACKED_PTR_HPP
