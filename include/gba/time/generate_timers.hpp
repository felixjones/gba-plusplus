#ifndef GBAXX_TIME_GENERATE_TIMERS_HPP
#define GBAXX_TIME_GENERATE_TIMERS_HPP

#include <chrono>

#include <gba/time/timer_control.hpp>

namespace gba {
namespace util {

using cycles = std::chrono::duration<uint32, std::ratio<1, 1 << 24>>;

namespace detail {

using cycles64_type = std::chrono::duration<unsigned long long, cycles::period>;

template <typename T>
constexpr unsigned int count_halves( T value ) noexcept {
    unsigned int counter = 0;
    while ( value > 1 ) {
        auto divisor = static_cast<uint16>( value & 0xffff );
        if ( divisor == 0 ) {
            value /= 0x10000;
        } else {
            value /= divisor;
        }
        counter++;
    }
    return counter;
}

template <unsigned Multiple, typename T>
constexpr auto round_to_nearest_multiple( T number ) noexcept {
    return ( ( number + Multiple / 2 ) / Multiple ) * Multiple;
}

template <typename T>
constexpr auto distance( T a, T b ) noexcept {
    return a > b ? a - b : b - a;
}

template <unsigned N>
constexpr auto generate_timers_inexact( std::array<timer_counter_control, N>& outArray, const cycles64_type::rep cycles ) noexcept {
    cycles64_type::rep clocks {};
    enum timer_control::cycles type {};
    int count {};

    const auto nearest1024 = round_to_nearest_multiple<1024>( cycles );
    const auto nearest256 = round_to_nearest_multiple<256>( cycles );
    const auto nearest64 = round_to_nearest_multiple<64>( cycles );

    const auto clock1024 = nearest1024 / 1024;
    const auto clock256 = nearest256 / 256;
    const auto clock64 = nearest64 / 64;

    const auto num1024 = count_halves( clock1024 );
    const auto num256 = count_halves( clock256 );
    const auto num64 = count_halves( clock64 );
    const auto num1 = count_halves( cycles );

    if ( num1024 <= N && nearest1024 == cycles ) {
        clocks = clock1024;
        type = timer_control::cycles::_1024;
        count = num1024;
    } else if ( num256 <= N && nearest256 == cycles ) {
        clocks = clock256;
        type = timer_control::cycles::_256;
        count = num256;
    } else if ( num64 <= N && nearest64 == cycles ) {
        clocks = clock64;
        type = timer_control::cycles::_64;
        count = num64;
    } else if ( num1 <= N ) {
        clocks = cycles;
        type = timer_control::cycles::_1;
        count = num1;
    } else {
        const auto distance1024 = distance( nearest1024, cycles );
        const auto distance256 = distance( nearest256, cycles );
        const auto distance64 = distance( nearest64, cycles );

        if ( num64 <= N && distance64 < distance256 && distance64 < distance1024 ) {
            clocks = clock64;
            type = timer_control::cycles::_64;
            count = num64;
        } else if ( num256 <= N && distance256 < distance1024 ) {
            clocks = clock256;
            type = timer_control::cycles::_256;
            count = num256;
        } else if ( num1024 <= N ) {
            clocks = clock1024;
            type = timer_control::cycles::_1024;
            count = num1024;
        } else {
            clocks = std::numeric_limits<cycles64_type::rep>::max();
            type = timer_control::cycles::_1024;
            count = N;
        }
    }

    for ( int ii = 0; ii < count; ++ii ) {
        auto counter = static_cast<uint16>( clocks & 0xffff );
        if ( counter == 0 ) {
            clocks /= 0x10000;
        } else {
            clocks /= counter;
        }
        counter = 0x10000 - counter;

        if ( ii == 0 ) {
            outArray[0] = timer_counter_control {
                .counter = counter,
                .control = timer_control {
                    .cycles = type,
                    .enable = true
                }
            };
        } else {
            outArray[ii] = timer_counter_control {
                .counter = counter,
                .control = timer_control {
                    .cascade = timer_control::cascade::on,
                    .enable = true
                }
            };
        }
    }

    return count;
}

} // detail

template <unsigned N, typename Rep, typename Period>
constexpr auto generate_timers( std::array<timer_counter_control, N>& outArray, const std::chrono::duration<Rep, Period>& duration ) noexcept {
    const auto cycles = std::chrono::round<detail::cycles64_type>( duration );
    return detail::generate_timers_inexact( outArray, cycles.count() );
}

} // util
} // gba

#endif // define GBAXX_TIME_GENERATE_TIMERS_HPP
