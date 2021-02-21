#ifndef GBAXX_EXT_AGBABI_INTERRUPT_HANDLERS_HPP
#define GBAXX_EXT_AGBABI_INTERRUPT_HANDLERS_HPP

#include <gba/types/interrupt_mask.hpp>
#include <gba/types/memmap.hpp>

#if defined( __agb_abi )

extern "C" {

void __agbabi_irq_empty();
void __agbabi_irq_user();

} // extern "C"

extern void ( * __agbabi_irq_uproc )( gba::interrupt_mask );

#endif

namespace gba {
namespace agbabi {

struct interrupt_handler : omemmap<void ( * )( void ), 0x3007FFC> {
    static void set( [[maybe_unused]] std::nullptr_t ) noexcept {
        omemmap::write( &__agbabi_irq_empty );
    }

    static void set( void ( * uproc )( interrupt_mask ) ) noexcept {
        __agbabi_irq_uproc = uproc;
        omemmap::write( &__agbabi_irq_user );
    }
};

[[gnu::constructor]]
inline void interrupt_handler_init() noexcept {
    interrupt_handler::set( nullptr );
}

} // agbabi
} // gba

#endif // define GBAXX_EXT_AGBABI_INTERRUPT_HANDLERS_HPP
