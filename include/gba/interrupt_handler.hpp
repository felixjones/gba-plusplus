#ifndef GBAXX_INTERRUPT_HANDLER_HPP
#define GBAXX_INTERRUPT_HANDLER_HPP

#include <cstddef>

#include <gba/interrupt.hpp>

extern "C" {

void _gba_intr_empty( void );
void _gba_intr_wrapped( void );
void _gba_intr_jump_table( void );

}

namespace gba {

#if __cplusplus >= 201703L

struct interrupt_condition {
	unsigned mask;
	void ( * function )( void );
};

template <class... Entries>
struct jump_table {
	const interrupt_condition table[sizeof...( Entries )];
	const int zero;

	constexpr jump_table( Entries&&... entries ) : table { std::forward<Entries>( entries )... }, zero( 0 ) {}
};

#else


// TODO : C++14 jump_table

#endif

namespace interrupt_handler {

#if __cplusplus >= 201703L

template <class JumpTable>
[[maybe_unused]]
inline void set( const JumpTable& table ) noexcept {
	using vector_type = void( * )( void );

	*( volatile const JumpTable ** )0x3000000 = &table;
	*( volatile vector_type * )0x3007FFC = _gba_intr_jump_table;
}

#else

  // TODO : C++14 set( const JumpTable& table )

#endif

[[maybe_unused]]
inline void set( [[maybe_unused]] std::nullptr_t ) noexcept {
	using vector_type = decltype( &_gba_intr_empty );

	*( volatile vector_type * )0x3007FFC = &_gba_intr_empty;
}

[[maybe_unused]]
inline void set( void ( * handler )( interrupt ) ) noexcept {
	using handler_type = decltype( handler );
	using vector_type = decltype( &_gba_intr_wrapped );

	*( volatile handler_type * )0x3000000 = handler;
	*( volatile vector_type * )0x3007FFC = &_gba_intr_wrapped;
}

[[maybe_unused]]
inline void set_raw( void ( * armHandler )( void ) ) noexcept {
	using vector_type = decltype( armHandler );

	*( volatile vector_type * )0x3007FFC = armHandler;
}

} // interrupt_handler
} // gba

#endif // define GBAXX_INTERRUPT_HANDLER_HPP
