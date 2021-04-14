#ifndef GBAXX_IO_BACKGROUND_MODE_HPP
#define GBAXX_IO_BACKGROUND_MODE_HPP

#include <gba/display/background_control.hpp>
#include <gba/types/screen_size.hpp>

namespace gba {
namespace io {

class background_control_regular {
public:
    constexpr background_control_regular() noexcept : m_data { 0, false, false, color_depth::color_16, 0, affine_background_wrap::clamp, screen_size::regular_32x32 } {}

    constexpr background_control_regular( const gba::background_control& displayControl ) noexcept : m_data { displayControl } {}

    constexpr operator gba::background_control() const noexcept {
        return m_data;
    }

    constexpr auto& set_priority( int v ) noexcept {
        m_data.priority = v;
        return *this;
    }

    constexpr auto get_priority() const noexcept {
        return m_data.priority;
    }

    constexpr auto& set_character_base_block( uint32 v ) noexcept {
        m_data.character_base_block = v;
        return *this;
    }

    constexpr auto get_character_base_block() const noexcept {
        return m_data.character_base_block;
    }

    constexpr auto& set_mosaic( bool v ) noexcept {
        m_data.mosaic = v;
        return *this;
    }

    constexpr auto get_mosaic() const noexcept {
        return m_data.mosaic;
    }

    constexpr auto& set_color_depth( gba::color_depth v ) noexcept {
        m_data.color_depth = v;
        return *this;
    }

    constexpr auto get_color_depth() const noexcept {
        return m_data.color_depth;
    }

    constexpr auto& set_screen_base_block( uint32 v ) noexcept {
        m_data.screen_base_block = v;
        return *this;
    }

    constexpr auto get_screen_base_block() const noexcept {
        return m_data.screen_base_block;
    }

    constexpr auto& set_screen_size( screen_size_regular v ) noexcept {
        m_data.screen_size = static_cast<gba::screen_size>( v );
        return *this;
    }

    constexpr auto get_screen_size() const noexcept {
        return static_cast<screen_size_regular>( m_data.screen_size );
    }

protected:
    gba::background_control m_data;

};

static_assert( sizeof( background_control_regular ) == 2, "background_control_regular must be tightly packed" );

class background_control_affine {
public:
    constexpr background_control_affine() noexcept : m_data { 0, false, false, color_depth::color_16, 0, affine_background_wrap::clamp, screen_size::regular_32x32 } {}

    constexpr background_control_affine( const gba::background_control& displayControl ) noexcept : m_data { displayControl } {}

    constexpr operator gba::background_control() const noexcept {
        return m_data;
    }

    constexpr auto& set_priority( int v ) noexcept {
        m_data.priority = v;
        return *this;
    }

    constexpr auto get_priority() const noexcept {
        return m_data.priority;
    }

    constexpr auto& set_character_base_block( int v ) noexcept {
        m_data.character_base_block = v;
        return *this;
    }

    constexpr auto get_character_base_block() const noexcept {
        return m_data.character_base_block;
    }

    constexpr auto& set_mosaic( bool v ) noexcept {
        m_data.mosaic = v;
        return *this;
    }

    constexpr auto get_mosaic() const noexcept {
        return m_data.mosaic;
    }

    constexpr auto& set_screen_base_block( int v ) noexcept {
        m_data.screen_base_block = v;
        return *this;
    }

    constexpr auto get_screen_base_block() const noexcept {
        return m_data.screen_base_block;
    }

    constexpr auto& set_background_wrap( gba::affine_background_wrap v ) noexcept {
        m_data.affine_background_wrap = v;
        return *this;
    }

    constexpr auto get_background_wrap() const noexcept {
        return m_data.affine_background_wrap;
    }

    constexpr auto& set_screen_size( screen_size_affine v ) noexcept {
        m_data.screen_size = static_cast<gba::screen_size>( v );
        return *this;
    }

    constexpr auto get_screen_size() const noexcept {
        return static_cast<screen_size_affine>( m_data.screen_size );
    }

protected:
    gba::background_control m_data;

};

static_assert( sizeof( background_control_affine ) == 2, "background_control_affine must be tightly packed" );

class background_control_bitmap {
public:
    constexpr background_control_bitmap() noexcept : m_data { 0, false, false, color_depth::color_16, 0, affine_background_wrap::clamp, screen_size::regular_32x32 } {}

    constexpr background_control_bitmap( const gba::background_control& displayControl ) noexcept : m_data { displayControl } {}

    constexpr operator gba::background_control() const noexcept {
        return m_data;
    }

    constexpr auto& set_priority( int v ) noexcept {
        m_data.priority = v;
        return *this;
    }

    constexpr auto get_priority() const noexcept {
        return m_data.priority;
    }

    constexpr auto& set_mosaic( bool v ) noexcept {
        m_data.mosaic = v;
        return *this;
    }

    constexpr auto get_mosaic() const noexcept {
        return m_data.mosaic;
    }

protected:
    gba::background_control m_data;

};

static_assert( sizeof( background_control_bitmap ) == 2, "background_control_bitmap must be tightly packed" );

} // io
} // gba

#endif // define GBAXX_IO_BACKGROUND_MODE_HPP
