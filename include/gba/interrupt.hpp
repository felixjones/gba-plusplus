#ifndef GBAXX_INTERRUPT_HPP
#define GBAXX_INTERRUPT_HPP

namespace gba {

struct interrupt {
	static constexpr interrupt make( void( *f )( interrupt& ) ) {
		interrupt value {};
		f( value );
		return value;
	}

	bool	vblank : 1,
			hblank : 1,
			vcount : 1,
			timer0 : 1,
			timer1 : 1,
			timer2 : 1,
			timer3 : 1,
			serial_communication : 1;

	bool	dma0 : 1,
			dma1 : 1,
			dma2 : 1,
			dma3 : 1,
			keypad : 1,
			game_pak : 1,
			: 2;

};

} // gba

#endif // define GBAXX_INTERRUPT_HPP
