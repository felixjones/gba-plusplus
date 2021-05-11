#ifndef GBAXX_TYPES_CYCLES_HPP
#define GBAXX_TYPES_CYCLES_HPP

#include <chrono>
#include <ratio>

#include <gba/types/int_type.hpp>

namespace gba {

using cycles_type = std::chrono::duration<uint32, std::ratio<1, 1 << 24>>;

namespace {

template <typename Rep, typename Period>
constexpr cycles_type cycles_from_duration( const std::duration<Rep, Period>& d ) noexcept {
    return std::chrono::round<cycle_type>( d );
}

constexpr auto cycles_per_frame = cycles_type( 280896 );
constexpr auto cycles_per_second = cycles_type( 1 << 24 );

}
} // gba

#endif // define GBAXX_TYPES_CYCLES_HPP
