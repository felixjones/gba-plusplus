#ifndef GBAXX_TYPES_DIMENSION_HPP
#define GBAXX_TYPES_DIMENSION_HPP

#include <gba/types/int_type.hpp>

namespace gba {

class dimension {
protected:
    static constexpr auto mask = 0xf;

public:
    class reference {
        friend dimension;
    public:
        [[nodiscard]]
        operator uint32() const noexcept {
            return ( ( data() >> shift() ) & mask ) + 1;
        }

        [[nodiscard]]
        constexpr operator bool() const noexcept {
            return true;
        }

        reference& operator =( const uint32 value ) noexcept {
            uint32 bits = data();
            bits &= mask << ( 4 - shift() );
            bits |= ( ( value - 1 ) & mask ) << shift();
            data() = bits;
            return *this;
        }

    protected:
        reference( uint8 * data ) noexcept : m_data { data } {}
        reference( uint8 * data, const bool ) noexcept : m_data { reinterpret_cast<uint8 *>( reinterpret_cast<uint32>( data ) | 0x80000000 ) } {}

    private:
        uint8 shift() const noexcept {
            return 4 * ( reinterpret_cast<uint32>( m_data ) >> 31 );
        }

        const uint8& data() const noexcept {
            return *reinterpret_cast<const uint8 *>( reinterpret_cast<uint32>( m_data ) & 0x7fffffff );
        }

        uint8& data() noexcept {
            return *reinterpret_cast<uint8 *>( reinterpret_cast<uint32>( m_data ) & 0x7fffffff );
        }

        uint8 * const m_data;
    };

    class const_reference {
        friend dimension;
    public:
        [[nodiscard]]
        operator uint32() const noexcept {
            return ( ( data() >> shift() ) & mask ) + 1;
        }

        [[nodiscard]]
        constexpr operator bool() const noexcept {
            return true;
        }

    protected:
        const_reference( const uint8 * data ) noexcept : m_data { data } {}
        const_reference( const uint8 * data, const bool ) noexcept : m_data { reinterpret_cast<const uint8 *>( reinterpret_cast<uint32>( data ) | 0x80000000 ) } {}

    private:
        uint8 shift() const noexcept {
            return 4 * ( reinterpret_cast<uint32>( m_data ) >> 31 );
        }

        const uint8& data() const noexcept {
            return *reinterpret_cast<const uint8 *>( reinterpret_cast<uint32>( m_data ) & 0x7fffffff );
        }

        const uint8 * const m_data;
    };

    constexpr dimension() noexcept : m_data { 0 } {}
    constexpr dimension( const dimension& o ) noexcept : m_data { o.m_data } {}

    constexpr dimension( uint32 width, uint32 height ) noexcept : m_data( ( ( height - 1 ) & mask ) << 4 | ( ( width - 1 ) & mask ) ) {}

    [[nodiscard]]
    reference width() noexcept {
        return reference( &m_data );
    }

    [[nodiscard]]
    const_reference width() const noexcept {
        return const_reference( &m_data );
    }

    [[nodiscard]]
    reference height() noexcept {
        return reference( &m_data, true );
    }

    [[nodiscard]]
    const_reference height() const noexcept {
        return const_reference( &m_data, true );
    }

private:
    uint8 m_data;
};

static_assert( sizeof( dimension ) == 1, "dimension must be tightly packed" );

} // gba

#endif // define GBAXX_TYPES_DIMENSION_HPP
