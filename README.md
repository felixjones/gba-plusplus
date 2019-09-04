## gba++

### Modern C++ library for Game Boy Advance

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

## Things to consider

### Interrupt vector?

Default interrupt vector must be an ARM function. Should we just let the user handle this?

Perhaps somehow wrap user vectors at compile-time somehow?

```cpp
void user_function_to_wrap( int regIF ) {}

// Wrap user function to support nested interrupts and Thumb functions?
const auto my_vector = gba::interrupt_handler<user_function_to_wrap>();

int main( int argc, char * argv[] ) {
  // Reading the current interrupt vector would be useful
  if ( gba::irq::vector() != my_vector ) {
    gba::irq::vector() = my_vector;
  }
  // ...
}
```

### What License?

Gravitating towards [Apache License 2.0](https://choosealicense.com/licenses/apache-2.0/) but this needs thought.

### Fixed point implementation?

Probably a thousand ways to do various fixed point operations.

GBA hardware should be kept in mind at all times.

Maybe also have a `fixed_fast` type that sacrifices any of the sanity checks?
