#ifndef GBAXX_IRQ_CONDITIONAL_HPP
#define GBAXX_IRQ_CONDITIONAL_HPP

#include <gba/irq_flags.hpp>

namespace gba {
namespace irq {

typedef void ( * runnable_type )( flags );

template <uint16 Mask, void ( * Runnable )( void )>
struct conditional {
	static constexpr auto mask = Mask;
	static constexpr auto runnable = Runnable;
};

} // irq
} // gba

#endif // define GBAXX_IRQ_CONDITIONAL_HPP