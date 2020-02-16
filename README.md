## gba++

### Modern Header-only C++ library for Game Boy Advance

## Philosophy

Where possible, try to keep some compatibility with [libgba](https://github.com/devkitPro/libgba).

The user manages memory (no static EWRAM/IWRAM allocations).

Interfaces to memory mapped types do not have state. Direct changes to memory should always be reflected in gba++ types.

Not a game engine.

No "tools". Just code.

STL used only where it makes "perfect" sense.

Do as much as possible at compile-time.

Cool things are separate library projects (SRAM, SD file system, RTC time, dynamic libraries, Nitro types). 

Types that reflect GBA hardware (24bit integers, fixed and frac decimals).

Some helpful, optional utilities (VRAM allocators, general allocators, perspective 3D matrices).

Explicit API, functions and types should be understandable in terms of GBA features (80 column IDEs are not a concern).

Do not stop the user from doing what they explicitly ask (addressing VRAM as Mode 3 whilst in Mode 0 should be possible).

The user decides if a header is compiled as ARM or Thumb.

## Style

Pretty much [Boost style](https://github.com/boostorg/geometry/wiki/Guidelines-for-Developers) but without the concern for 80 column IDEs.

Everything is within a `gba::` namespace.

Use gba++ types `gba::int16 gba::uint16` and keep volatile as a separate keyword.

## Sample code

```C++
#include <gba/gba.hpp>

#define EVER ;;

typedef gba::color mode3_line[240];

static auto& DISPCNT = gba::io::display::control;
static auto& mode3_memory = ( mode3_line * )0x6000000;

int main( int argc, char * argv[] ) {
	DISPCNT.write( gba::display::control { .mode = 3, .background_layer2 = true } );

	mode3_memory[80][120] = gba::color { .red = 31, .green =  0, .blue =  0 };
	mode3_memory[80][136] = gba::color { .red =  0, .green = 31, .blue =  0 };
	mode3_memory[96][120] = gba::color { .red =  0, .green =  0, .blue = 31 };

	for ( EVER ) {}
	return 0;
}
```

## Things to consider

### What License?

Gravitating towards [Apache License 2.0](https://choosealicense.com/licenses/apache-2.0/) but this needs thought.

### Fixed point implementation?

Probably a thousand ways to do various fixed point operations.

GBA hardware should be kept in mind at all times.

Maybe also have a `fixed_fast` type that sacrifices accuracy and checks?
