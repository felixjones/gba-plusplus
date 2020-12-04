#ifndef GBAXX_VIDEO_PALETTE_HPP
#define GBAXX_VIDEO_PALETTE_HPP

#include <memory>

#include <gba/types/color.hpp>
#include <gba/types/int_type.hpp>

namespace gba {

/**
 *
 * @tparam PaletteDef
 */
template <typename PaletteDef>
struct palette : PaletteDef {
    using value_type = typename PaletteDef::value_type;
    using size_type = typename PaletteDef::size_type;
    using difference_type = typename PaletteDef::difference_type;
    using reference = typename PaletteDef::reference;
    using const_reference = typename PaletteDef::const_reference&;
    using pointer = typename PaletteDef::pointer&;
    using const_pointer = typename PaletteDef::const_pointer&;
    using iterator = typename PaletteDef::iterator;
    using const_iterator = typename PaletteDef::const_iterator;

    reference at( size_type pos ) noexcept {
        return PaletteDef::at( pos );
    }

    const_reference at( size_type pos ) const noexcept {
        return PaletteDef::at( pos );
    }

    reference operator []( size_type pos ) noexcept {
        return PaletteDef::at( pos );
    }

    const_reference operator []( size_type pos ) const noexcept {
        return PaletteDef::at( pos );
    }

    reference front() noexcept {
        return PaletteDef::front();
    }

    const_reference front() const noexcept {
        return PaletteDef::front();
    }

    reference back() noexcept {
        return PaletteDef::back();
    }

    const_reference back() const noexcept {
        return PaletteDef::back();
    }

    pointer data() noexcept {
        return PaletteDef::data();
    }

    const_pointer data() const noexcept {
        return PaletteDef::data();
    }

    iterator begin() noexcept {
        return PaletteDef::begin();
    }

    const_iterator cbegin() noexcept {
        return PaletteDef::cbegin();
    }

    iterator end() noexcept {
        return PaletteDef::end();
    }

    const_iterator cend() noexcept {
        return PaletteDef::end();
    }
};

/**
 *
 * @tparam Address
 * @tparam Length
 */
template <unsigned Address, unsigned Length>
struct palette_definition {
    using value_type = color::rgb555;
    using size_type = uint32;
    using difference_type = int32;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type *;
    using const_pointer = const value_type *;

    /**
     *
     */
    class iterator {
    public:
        using value_type = color::rgb555;
        using size_type = uint32;
        using difference_type = int32;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type *;
        using const_pointer = const value_type *;

        constexpr explicit iterator( size_type pos ) noexcept : m_pos { pos } {}

        bool operator ==( const iterator& other ) const noexcept {
            return m_pos == other.m_pos;
        }

        bool operator !=( const iterator& other ) const noexcept {
            return m_pos != other.m_pos;
        }

        reference operator *() noexcept {
            return at( m_pos );
        }

        pointer operator ->() noexcept {
            return data() + m_pos;
        }

        iterator& operator=( const iterator& other ) noexcept {
            m_pos = other.m_pos;
            return *this;
        }

        iterator operator ++( int ) noexcept {
            return iterator( m_pos++ );
        }

        iterator& operator ++() noexcept {
            ++m_pos;
            return *this;
        }

    protected:
        size_type m_pos;
    };

    /**
     *
     */
    class const_iterator {
    public:
        using value_type = color::rgb555;
        using size_type = uint32;
        using difference_type = int32;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type *;
        using const_pointer = const value_type *;

        constexpr explicit const_iterator( size_type pos ) noexcept : m_pos { pos } {}

        bool operator ==( const const_iterator& other ) const noexcept {
            return m_pos == other.m_pos;
        }

        bool operator !=( const const_iterator& other ) const noexcept {
            return m_pos != other.m_pos;
        }

        const_reference operator *() noexcept {
            return at( m_pos );
        }

        const_pointer operator ->() noexcept {
            return data() + m_pos;
        }

        const_iterator& operator=( const const_iterator& other ) noexcept {
            m_pos = other.m_pos;
            return *this;
        }

        const_iterator operator ++( int ) noexcept {
            return iterator( m_pos++ );
        }

        const_iterator& operator ++() noexcept {
            ++m_pos;
            return *this;
        }

    protected:
        size_type m_pos;
    };

    static reference at( size_type pos ) noexcept {
        return data()[pos];
    }

    static reference front() noexcept {
        return *data();
    }

    static reference back() noexcept {
        return at( Length - 1 );
    }

    static pointer data() noexcept {
        return std::launder( reinterpret_cast<pointer>( Address ) );
    }

    static iterator begin() noexcept {
        return iterator( 0 );
    }

    static const_iterator cbegin() noexcept {
        return const_iterator( 0 );
    }

    static iterator end() noexcept {
        return iterator( Length );
    }

    static const_iterator cend() noexcept {
        return const_iterator( Length );
    }
};

using palette_background_8pp = palette_definition<0x5000000, 256>;
using palette_object_8pp = palette_definition<0x5000200, 256>;

/**
 *
 * @tparam Address
 * @tparam Length
 */
template <unsigned Address, unsigned Length>
struct palette_bank_definition {
    using value_type = color::rgb555;
    using size_type = uint32;
    using difference_type = int32;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type *;
    using const_pointer = const value_type *;

    /**
     *
     */
    class iterator {
    public:
        using value_type = color::rgb555;
        using size_type = uint32;
        using difference_type = int32;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type *;
        using const_pointer = const value_type *;

        constexpr explicit iterator( palette_bank_definition& owner, size_type pos ) noexcept : m_owner { owner }, m_pos { pos } {}

        bool operator ==( const iterator& other ) const noexcept {
            return m_owner.bank == other.m_owner.bank && m_pos == other.m_pos;
        }

        bool operator !=( const iterator& other ) const noexcept {
            return m_owner.bank != other.m_owner.bank || m_pos != other.m_pos;
        }

        reference operator *() noexcept {
            return m_owner.at( m_pos );
        }

        pointer operator ->() noexcept {
            return m_owner.data() + m_pos;
        }

        iterator& operator=( const iterator& other ) noexcept {
            m_pos = other.m_pos;
            return *this;
        }

        iterator operator ++( int ) noexcept {
            return iterator( m_owner, m_pos++ );
        }

        iterator& operator ++() noexcept {
            ++m_pos;
            return *this;
        }

    protected:
        palette_bank_definition& m_owner;
        size_type m_pos;
    };

    /**
     *
     */
    class const_iterator {
    public:
        using value_type = color::rgb555;
        using size_type = uint32;
        using difference_type = int32;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type *;
        using const_pointer = const value_type *;

        constexpr explicit const_iterator( const palette_bank_definition& owner, size_type pos ) noexcept : m_owner { owner }, m_pos { pos } {}

        bool operator ==( const const_iterator& other ) const noexcept {
            return m_owner.bank == other.m_owner.bank && m_pos == other.m_pos;
        }

        bool operator !=( const const_iterator& other ) const noexcept {
            return m_owner.bank != other.m_owner.bank || m_pos != other.m_pos;
        }

        const_reference operator *() noexcept {
            return m_owner.at( m_pos );
        }

        const_pointer operator ->() noexcept {
            return m_owner.data() + m_pos;
        }

        const_iterator& operator=( const const_iterator& other ) noexcept {
            m_pos = other.m_pos;
            return *this;
        }

        const_iterator operator ++( int ) noexcept {
            return const_iterator( m_owner, m_pos++ );
        }

        const_iterator& operator ++() noexcept {
            ++m_pos;
            return *this;
        }

    protected:
        const palette_bank_definition& m_owner;
        size_type m_pos;
    };

    constexpr explicit palette_bank_definition( size_type b ) noexcept : bank { b } {}

    reference at( size_type pos ) noexcept {
        return data()[pos];
    }

    [[nodiscard]]
    const_reference at( size_type pos ) const noexcept {
        return data()[pos];
    }

    reference operator []( size_type pos ) noexcept {
        return at( pos );
    }

    [[nodiscard]]
    const_reference operator []( size_type pos ) const noexcept {
        return at( pos );
    }

    reference front() noexcept {
        return *data();
    }

    [[nodiscard]]
    const_reference front() const noexcept {
        return *data();
    }

    reference back() noexcept {
        return at( Length - 1 );
    }

    [[nodiscard]]
    const_reference back() const noexcept {
        return at( Length - 1 );
    }

    pointer data() noexcept {
        return std::launder( reinterpret_cast<pointer>( Address ) + ( bank * Length ) );
    }

    [[nodiscard]]
    const_pointer data() const noexcept {
        return std::launder( reinterpret_cast<pointer>( Address ) + ( bank * Length ) );
    }

    iterator begin() noexcept {
        return iterator( *this, 0 );
    }

    const_iterator cbegin() noexcept {
        return const_iterator( *this, 0 );
    }

    iterator end() noexcept {
        return iterator( *this, Length );
    }

    const_iterator cend() noexcept {
        return const_iterator( *this, Length );
    }

    const size_type bank;
};

using palette_background_4pp = palette_bank_definition<0x5000000, 16>;
using palette_object_4pp = palette_bank_definition<0x5000200, 16>;

} // gba

#endif // GBAXX_VIDEO_PALETTE_HPP
