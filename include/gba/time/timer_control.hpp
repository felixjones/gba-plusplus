#ifndef GBAXX_TIME_TIMER_CONTROL_HPP
#define GBAXX_TIME_TIMER_CONTROL_HPP

#include <gba/types/int_type.hpp>

namespace gba {

struct timer_control {
    enum class cycles : uint16 {
        _1 = 0,
        _64 = 1,
        _256 = 2,
        _1024 = 3
    };

    enum class cascade : bool {
        off = false,
        on = true,

        overflow = on
    };

    timer_control::cycles cycles : 2;
    timer_control::cascade cascade : 1;
    uint16 : 3;
    bool timer_irq : 1,
        enable : 1;
    uint16 : 8;
};

static_assert( sizeof( timer_control ) == 2, "timer_control must be tightly packed" );

struct timer_counter_control {
    uint16 counter;
    timer_control control;
};

static_assert( sizeof( timer_counter_control ) == 4, "timer_counter_control must be tightly packed" );

} // gba

#endif // define GBAXX_TIME_TIMER_CONTROL_HPP
