#ifndef GBAXX_ALLOCATOR_BUFFER_HPP
#define GBAXX_ALLOCATOR_BUFFER_HPP

#include <gba/types/int_type.hpp>

namespace gba {
namespace allocator {

class buffer {
public:
    constexpr buffer( const uint32 address, const uint32 x, const uint32 y, const uint32 width, const uint32 height ) noexcept : m_address( address ), m_x( x ), m_y( y ), m_width( width ), m_height( height ) {}
    constexpr buffer( std::nullptr_t&& ) noexcept : m_address(), m_x(), m_y(), m_width(), m_height() {}

    constexpr operator bool() const noexcept {
        return m_address;
    }

    constexpr bool operator ==( const buffer& o ) const noexcept {
        return m_address == o.m_address;
    }

    constexpr bool operator !=( const buffer& o ) const noexcept {
        return m_address != o.m_address;
    }

    constexpr bool operator ==( std::nullptr_t&& ) const noexcept {
        return !m_address;
    }

    constexpr bool operator !=( std::nullptr_t&& ) const noexcept {
        return m_address;
    }

protected:
    friend class bitset_access;

    uint32 m_address;
    uint8 m_x;
    uint8 m_y;
    uint8 m_width;
    uint8 m_height;
};

} // allocator
} // gba

#endif // define GBAXX_ALLOCATOR_BUFFER_HPP
