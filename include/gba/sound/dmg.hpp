#ifndef GBAXX_SOUND_DMG_HPP
#define GBAXX_SOUND_DMG_HPP

#include <array>
#include <chrono>

#include <gba/types/int_type.hpp>

namespace gba {
namespace sound {

enum class direction : bool {
    increment = false,
    decrement = true,

    up = false,
    down = true,

    increasing = false,
    decreasing = true,

    increase = false,
    decrease = true
};

enum class time : uint16 {
    off = 0,

    khz_1_128 = 1,
    khz_2_128 = 2,
    khz_3_128 = 3,
    khz_4_128 = 4,
    khz_5_128 = 5,
    khz_6_128 = 6,
    khz_7_128 = 7,

    ms_7_8125 = 1,
    ms_15_625 = 2,
    ms_23_4375 = 3,
    ms_31_25 = 4,
    ms_39_0625 = 5,
    ms_46_875 = 6,
    ms_54_6875 = 7
};

struct sweep {
    template <class Duration>
    static constexpr auto time_from( const Duration& duration ) noexcept {
        using duration_type = typename std::chrono::duration<int, std::ratio<1, 128>>;

        return sound::time( std::chrono::round<duration_type>( duration ).count() );
    }

    uint16 shift : 3;
    sound::direction direction : 1;
    sound::time time : 3;
};

static_assert( sizeof( sweep ) == 2, "sweep must be tightly packed" );

enum class duty : uint16 {
    percentage_12_5 = 0,
    percentage_25 = 1,
    percentage_50 = 2,
    percentage_75 = 3,

    _1_8 = 0,
    _2_8 = 1,
    _4_8 = 2,
    _6_8 = 3,

    _1_4 = 1,
    _2_4 = 2,
    _3_4 = 3,

    _1_2 = 2,

    eighth = 0,
    quarter = 1,
    half = 2,
    three_quarters = 3
};

enum class step : uint16 {
    off = 0,

    ms_15_625 = 1,
    ms_31_25 = 2,
    ms_46_875 = 3,
    ms_62_5 = 4,
    ms_78_125 = 5,
    ms_93_75 = 6,
    ms_109_375 = 7,

    hz_64 = 1,
    hz_32 = 2,
    hz_21_333 = 3,
    hz_16 = 4,
    hz_12_8 = 5,
    hz_10_666 = 6,
    hz_9_174 = 7
};

struct square_control {
    template <class Duration>
    static constexpr auto length_from( const Duration& duration ) noexcept {
        using duration_type = typename std::chrono::duration<int, std::ratio<1, 256>>;

        return 64 - std::chrono::round<duration_type>( duration ).count();
    }

    template <class Duration>
    static constexpr auto step_from( const Duration& duration ) noexcept {
        using duration_type = typename std::chrono::duration<int, std::ratio<1, 64>>;

        return sound::step( std::chrono::round<duration_type>( duration ).count() );
    }

    uint16 length : 6;
    sound::duty duty : 2;
    sound::step step : 3;
    sound::direction direction : 1;
    uint16 volume : 4;
};

static_assert( sizeof( square_control ) == 2, "square_control must be tightly packed" );

enum class timed : bool {
    hold = false,
    timed = true,

    loop = false,
    continuous = false,
    one_shot = true
};

struct square_frequency {
    template <class Duration>
    static constexpr auto frequency_from( const Duration& duration ) noexcept {
        using duration_type = typename std::chrono::duration<int, std::ratio<1, 0x400000>>;

        return ( 0x10000 / std::chrono::round<duration_type>( duration ).count() ) - 1;
    }

    uint16 frequency : 11,
        : 3;
    sound::timed timed : 1;
    bool reset : 1;
};

static_assert( sizeof( square_frequency ) == 2, "square_frequency must be tightly packed" );

enum class bank_size : uint16 {
    one = 0,
    two = 1,

    nibbles_32 = 0,
    nibbles_64 = 1
};

struct wave_select {
    uint16 : 5;
    sound::bank_size bank_size : 1;
    uint16 current_bank : 1;
    bool enable : 1;
    uint16 : 8;
};

static_assert( sizeof( wave_select ) == 2, "wave_select must be tightly packed" );

enum class wave_volume : uint16 {
    zero = 0,
    full = 1,
    half = 2,
    quarter = 3,
    three_quarters = 4,

    percentage_0 = zero,
    percentage_100 = full,
    percentage_50 = half,
    percentage_25 = quarter,
    percentage_75 = three_quarters
};

struct wave_control {
    template <class Duration>
    static constexpr auto length_from( const Duration& duration ) noexcept {
        using duration_type = typename std::chrono::duration<int, std::ratio<1, 256>>;

        return std::chrono::round<duration_type>( duration ).count();
    }

    uint16 length : 8,
        : 5;
    wave_volume volume : 3;
};

static_assert( sizeof( wave_control ) == 2, "wave_control must be tightly packed" );

struct wave_frequency {
    template <class Duration>
    static constexpr auto frequency_from( const Duration& duration ) noexcept {
        using duration_type = typename std::chrono::duration<int, std::ratio<1, 0x400000>>;

        return ( 0x10000 / std::chrono::round<duration_type>( duration ).count() ) - 1;
    }

    uint16 frequency : 11,
            : 3;
    sound::timed timed : 1;
    bool reset : 1;
};

static_assert( sizeof( wave_frequency ) == 2, "wave_frequency must be tightly packed" );

using wave_ram = std::array<uint32, 4>;

struct noise_control {
    template <class Duration>
    static constexpr auto length_from( const Duration& duration ) noexcept {
        using duration_type = typename std::chrono::duration<int, std::ratio<1, 256>>;

        return 64 - std::chrono::round<duration_type>( duration ).count();
    }

    template <class Duration>
    static constexpr auto step_from( const Duration& duration ) noexcept {
        using duration_type = typename std::chrono::duration<int, std::ratio<1, 64>>;

        return sound::step( std::chrono::round<duration_type>( duration ).count() );
    }

    uint16 length : 6,
        : 2;
    sound::step step : 3;
    sound::direction direction : 1;
    uint16 volume : 4;
};

static_assert( sizeof( noise_control ) == 2, "noise_control must be tightly packed" );

enum class clock_multiplier : uint16 {
    two = 0,
    one = 1,
    half = 2,
    third = 3,
    forth = 4,
    fifth = 5,
    sixth = 6,
    seventh = 7
};

enum class counter_stages : bool {
    _15 = false,
    _7 = true
};

enum class counter_pre_step_frequency : uint16 {
    two = 0,
    one = 1,
    half = 2,
    third = 3,
    forth = 4,
    fifth = 5,
    sixth = 6,
    seventh = 7
};

struct noise_frequency {
    sound::clock_multiplier clock_multiplier : 3;
    sound::counter_stages counter_stages : 1;
    uint16 shift_frequency : 4,
        : 6;
    sound::timed timed : 1;
    bool reset : 1;
};

static_assert( sizeof( noise_frequency ) == 2, "noise_frequency must be tightly packed" );

struct dmg_control {
    uint16 volume_right : 3,
            : 1;
    uint16 volume_left : 3,
            : 1;
    bool right_square1 : 1,
            right_square2 : 1,
            right_wave : 1,
            right_noise : 1,
            left_square1 : 1,
            left_square2 : 1,
            left_wave : 1,
            left_noise : 1;
};

static_assert( sizeof( dmg_control ) == 2, "dmg_control must be tightly packed" );

} // sound
} // gba

#endif // define GBAXX_SOUND_DMG_HPP
