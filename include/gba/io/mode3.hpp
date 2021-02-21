#ifndef GBAXX_IO_MODE3_HPP
#define GBAXX_IO_MODE3_HPP

#include <gba/display/display_control.hpp>
#include <gba/io/io.hpp>

namespace gba {
namespace io {

template <>
struct mode<3> {

    static constexpr auto value = 3;

    class display_control {
    public:
        constexpr display_control() noexcept : m_data { .mode = value } {}

        constexpr display_control( const gba::display_control& displayControl ) noexcept : m_data { displayControl } {
            m_data.mode = value;
        }

        constexpr operator gba::display_control() const noexcept {
            return m_data;
        }

        constexpr auto& set_oam_hblank_access( oam_hblank_access v ) noexcept {
            m_data.oam_hblank_access = v;
            return *this;
        }

        constexpr auto get_oam_hblank_access() const noexcept {
            return m_data.oam_hblank_access;
        }

        constexpr auto& set_object_tile_map( object_tile_map v ) noexcept {
            m_data.object_tile_map = v;
            return *this;
        }

        constexpr auto get_object_tile_map() const noexcept {
            return m_data.object_tile_map;
        }

        constexpr auto& set_layer_background_2( bool v ) noexcept {
            m_data.layer_background_2 = v;
            return *this;
        }

        constexpr auto get_layer_background_2() const noexcept {
            return m_data.layer_background_2;
        }

        constexpr auto& set_layer_object( bool v ) noexcept {
            m_data.layer_object = v;
            return *this;
        }

        constexpr auto get_layer_object() const noexcept {
            return m_data.layer_object;
        }

        constexpr auto& set_window_0( bool v ) noexcept {
            m_data.window_0 = v;
            return *this;
        }

        constexpr auto get_window_0() const noexcept {
            return m_data.window_0;
        }

        constexpr auto& set_window_1( bool v ) noexcept {
            m_data.window_1 = v;
            return *this;
        }

        constexpr auto get_window_1() const noexcept {
            return m_data.window_1;
        }

        constexpr auto& set_window_object( bool v ) noexcept {
            m_data.window_object = v;
            return *this;
        }

        constexpr auto get_window_object() const noexcept {
            return m_data.window_object;
        }

    protected:
        gba::display_control m_data;

    };

    static_assert( sizeof( display_control ) == 2, "mode<3>::display_control must be tightly packed" );

};

} // io
} // gba

#endif // define GBAXX_IO_MODE3_HPP
