#ifndef GBAXX_KEYPAD_KEYPAD_HPP
#define GBAXX_KEYPAD_KEYPAD_HPP

namespace gba {

struct keypad {
    bool button_a : 1,
            button_b : 1,
            select : 1,
            start : 1,
            right : 1,
            left : 1,
            up : 1,
            down : 1,
            button_r : 1,
            button_l : 1;
};

static_assert( sizeof( keypad ) == 2, "keypad must be tightly packed" );

struct keypad_control {
    bool button_a : 1,
            button_b : 1,
            select : 1,
            start : 1,
            right : 1,
            left : 1,
            up : 1,
            down : 1,
            button_r : 1,
            button_l : 1,
            : 4,
            keypad_irq : 1,
            irq_operator_and : 1;
};

static_assert( sizeof( keypad_control ) == 2, "keypad_control must be tightly packed" );

} // gba

#endif // define GBAXX_KEYPAD_KEYPAD_HPP
