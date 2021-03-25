#ifndef GBAXX_KEYPAD_KEYPAD_MANAGER_HPP
#define GBAXX_KEYPAD_KEYPAD_MANAGER_HPP

#include <gba/keypad/keypad.hpp>
#include <gba/types/memmap.hpp>
#include <gba/types/int_type.hpp>

namespace gba {

class key_mask {
public:
    template <typename ...Args>
    static constexpr key_mask make( Args... args ) noexcept {
        return key_mask( ( args.m_data | ... ) );
    }

    constexpr key_mask( const uint32 intMask ) noexcept : m_data { intMask } {}

    constexpr operator uint32() const noexcept {
        return m_data;
    }

protected:
    uint32 m_data;
};

static_assert( sizeof( key_mask ) == 4, "key_mask must be tightly packed" );

namespace key {
namespace {

constexpr auto button_a = key_mask { 0x1 << 0 };
constexpr auto button_b = key_mask { 0x1 << 1 };
constexpr auto select = key_mask { 0x1 << 2 };
constexpr auto start = key_mask { 0x1 << 3 };
constexpr auto right = key_mask { 0x1 << 4 };
constexpr auto left = key_mask { 0x1 << 5 };
constexpr auto up = key_mask { 0x1 << 6 };
constexpr auto down = key_mask { 0x1 << 7 };
constexpr auto button_r = key_mask { 0x1 << 8 };
constexpr auto button_l = key_mask { 0x1 << 9 };

}
} // key

template <class KeypadSource>
class keypad_manager {
    static_assert( std::is_same_v<keypad, typename KeypadSource::type>, "keypad_manager requires keypad source" );
public:
    constexpr keypad_manager() noexcept : m_keys { 0x3ff }, m_xor { 0 } {}

    auto& poll() noexcept {
        poll_switches();
        m_keys ^= m_xor;
        return *this;
    }

    [[nodiscard]]
    constexpr int32 axis_x() const noexcept {
        return -( ( m_keys & key::left ) == 0 ) + ( ( m_keys & key::right ) == 0 );
    }

    [[nodiscard]]
    constexpr int32 axis_y() const noexcept {
        return -( ( m_keys & key::up ) == 0 ) + ( ( m_keys & key::down ) == 0 );
    }

    [[nodiscard]]
    constexpr bool is_down( key_mask mask ) const noexcept {
        return ( m_keys & mask ) == 0;
    }

    [[nodiscard]]
    constexpr bool is_up( key_mask mask ) const noexcept {
        return ( m_keys & mask ) != 0;
    }

    [[nodiscard]]
    constexpr bool is_switched( key_mask mask ) const noexcept {
        return ( m_xor & mask ) == mask;
    }

    [[nodiscard]]
    constexpr bool switched_down( key_mask mask ) const noexcept {
        return is_switched( mask ) && is_down( mask );
    }

    [[nodiscard]]
    constexpr bool switched_up( key_mask mask ) const noexcept {
        return is_switched( mask ) && is_up( mask );
    }

protected:
    [[gnu::always_inline]]
    void poll_switches() volatile noexcept {
        m_xor = m_keys ^ imemmap<uint16, KeypadSource::address>::read();
    }

    uint16 m_keys;
    uint16 m_xor;

};

static_assert( sizeof( keypad_manager<imemmap<keypad, 0>> ) == 4, "keypad_manager must be tightly packed" );

} // gba

#endif // define GBAXX_KEYPAD_KEYPAD_MANAGER_HPP
