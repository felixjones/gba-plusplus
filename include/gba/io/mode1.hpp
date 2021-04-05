#ifndef GBAXX_IO_MODE1_HPP
#define GBAXX_IO_MODE1_HPP

#include <gba/display/display_control.hpp>
#include <gba/io/background_matrix.hpp>
#include <gba/io/io.hpp>

namespace gba {
namespace io {

template <>
struct mode<1> {

    static constexpr auto value = 1;

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

    static_assert( sizeof( display_control ) == 2, "mode<1>::display_control must be tightly packed" );

    using background_control_0 = background_control_regular;
    using background_control_1 = background_control_regular;
    using background_control_2 = background_control_affine;

    struct reg {
        using bg0cnt = iomemmap<background_control_0, 0x4000008>;
        using bg1cnt = iomemmap<background_control_1, 0x400000a>;
        using bg2cnt = iomemmap<background_control_2, 0x400000c>;

        using bg0hofs = omemmap<int16, 0x4000010>;
        using bg0vofs = omemmap<int16, 0x4000012>;

        using bg1hofs = omemmap<int16, 0x4000014>;
        using bg1vofs = omemmap<int16, 0x4000016>;

        using bg0ofs_vec2 = omemmap<vec2<int16>, 0x4000010>;
        using bg1ofs_vec2 = omemmap<vec2<int16>, 0x4000014>;

        using bg2pa = omemmap<make_fixed<7, 8>, 0x4000020>;
        using bg2pb = omemmap<make_fixed<7, 8>, 0x4000022>;
        using bg2pc = omemmap<make_fixed<7, 8>, 0x4000024>;
        using bg2pd = omemmap<make_fixed<7, 8>, 0x4000026>;
        using bg2x = omemmap<make_fixed<19, 8>, 0x4000028>;
        using bg2y = omemmap<make_fixed<19, 8>, 0x400002c>;

        using bg2_mat2 = omemmap<io::background_mat2, 0x4000020>;
        using bg2_mat3x2 = omemmap<io::background_mat3x2, 0x4000020>;
        using bg2_vec2 = omemmap<vec2<make_fixed<19, 8>>, 0x4000028>;
    };
};

} // io
} // gba

#endif // define GBAXX_IO_MODE1_HPP
