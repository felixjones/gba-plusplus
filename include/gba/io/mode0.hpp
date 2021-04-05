#ifndef GBAXX_IO_MODE0_HPP
#define GBAXX_IO_MODE0_HPP

#include <gba/display/display_control.hpp>
#include <gba/io/background_mode.hpp>
#include <gba/io/io.hpp>
#include <gba/types/vector/vec2.hpp>
#include <gba/vram/vram_obj_allocator.hpp>

namespace gba {
namespace io {

template <>
struct mode<0> {

    static constexpr auto value = 0;

    class display_control {
    public:
        constexpr display_control() noexcept : m_data { value, false, 0, oam_hblank_access::locked, object::tile_map::two_dimensional, false,
                                                        false, false, false, false, false, false, false,
                                                        false } {}

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

        constexpr auto& set_object_tile_map( object::tile_map v ) noexcept {
            m_data.object_tile_map = v;
            return *this;
        }

        constexpr auto get_object_tile_map() const noexcept {
            return m_data.object_tile_map;
        }

        constexpr auto& set_layer_background_0( bool v ) noexcept {
            m_data.layer_background_0 = v;
            return *this;
        }

        constexpr auto get_layer_background_0() const noexcept {
            return m_data.layer_background_0;
        }

        constexpr auto& set_layer_background_1( bool v ) noexcept {
            m_data.layer_background_1 = v;
            return *this;
        }

        constexpr auto get_layer_background_1() const noexcept {
            return m_data.layer_background_1;
        }

        constexpr auto& set_layer_background_2( bool v ) noexcept {
            m_data.layer_background_2 = v;
            return *this;
        }

        constexpr auto get_layer_background_2() const noexcept {
            return m_data.layer_background_2;
        }

        constexpr auto& set_layer_background_3( bool v ) noexcept {
            m_data.layer_background_3 = v;
            return *this;
        }

        constexpr auto get_layer_background_3() const noexcept {
            return m_data.layer_background_3;
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

    static_assert( sizeof( display_control ) == 2, "mode<0>::display_control must be tightly packed" );

    using background_control = background_control_regular;

    struct reg {
        reg() = delete;

        using bg0cnt = iomemmap<background_control, 0x4000008>;
        using bg1cnt = iomemmap<background_control, 0x400000a>;
        using bg2cnt = iomemmap<background_control, 0x400000c>;
        using bg3cnt = iomemmap<background_control, 0x400000c>;

        using bg0hofs = omemmap<int16, 0x4000010>;
        using bg0vofs = omemmap<int16, 0x4000012>;

        using bg1hofs = omemmap<int16, 0x4000014>;
        using bg1vofs = omemmap<int16, 0x4000016>;

        using bg2hofs = omemmap<int16, 0x4000018>;
        using bg2vofs = omemmap<int16, 0x400001a>;

        using bg3hofs = omemmap<int16, 0x400001c>;
        using bg3vofs = omemmap<int16, 0x400001e>;

        using bg0ofs_vec2 = omemmap<vec2<int16>, 0x4000010>;
        using bg1ofs_vec2 = omemmap<vec2<int16>, 0x4000014>;
        using bg2ofs_vec2 = omemmap<vec2<int16>, 0x4000018>;
        using bg3ofs_vec2 = omemmap<vec2<int16>, 0x400001c>;
    };

    using obj_allocator = vram::obj_allocator<32u, 0x6010000>;
};

} // io
} // gba

#endif // define GBAXX_IO_MODE0_HPP
