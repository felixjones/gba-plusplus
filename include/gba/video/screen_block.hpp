#ifndef GBAXX_VIDEO_SCREEN_BLOCK_HPP
#define GBAXX_VIDEO_SCREEN_BLOCK_HPP

#include <gba/types/int_type.hpp>

namespace gba {

struct tile_entry_regular {
    uint16 index : 10;
    bool flip_x : 1, flip_y : 1;
    uint16 palette_bank : 4;
};

static_assert( sizeof( tile_entry_regular ) == 2, "tile_entry_regular must be tightly packed" );

struct tile_entry_affine {
    uint8 index;
};

static_assert( sizeof( tile_entry_affine ) == 1, "tile_entry_affine must be tightly packed" );

template <unsigned Address, class EntryType, unsigned Length>
struct screen_definition {
    using value_type = EntryType;
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
        using iterator_category = std::forward_iterator_tag;

        using value_type = EntryType;
        using size_type = uint32;
        using difference_type = int32;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type *;
        using const_pointer = const value_type *;

        constexpr explicit iterator( screen_definition& owner, size_type pos ) noexcept : m_owner { owner }, m_pos { pos } {}

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
        screen_definition& m_owner;
        size_type m_pos;
    };

    /**
     *
     */
    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;

        using value_type = EntryType;
        using size_type = uint32;
        using difference_type = int32;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type *;
        using const_pointer = const value_type *;

        constexpr explicit const_iterator( const screen_definition& owner, size_type pos ) noexcept : m_owner { owner }, m_pos { pos } {}

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
        const screen_definition& m_owner;
        size_type m_pos;
    };

    constexpr explicit screen_definition( size_type b ) noexcept : bank { b } {}

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

    size_type bank;
};

using screen_block_regular = screen_definition<0x6000000, tile_entry_regular, 1024>;
using screen_block_affine = screen_definition<0x6000000, tile_entry_affine, 1024>;

} // gba

#endif // define GBAXX_VIDEO_SCREEN_BLOCK_HPP
