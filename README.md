# gba-plusplus

Modern drop-in C++ library for the Game Boy Advance. Zlib license.

# Example

```C++
#include <gba/gba.hpp>

using namespace gba;

using video_memory_type = std::array<std::array<uint16, 240>, 160>;

static auto& video_memory = *reinterpret_cast<video_memory_type *>( 0x06000000 );

struct bgr555_type {
    uint16 red : 5;
    uint16 green : 5;
    uint16 blue : 5;
};

int main() {
    reg::dispcnt::write( { .mode = 3, .layer_background_2 = true } );
    
    video_memory[80][120] = uint_cast( bgr555_type { .red = 31 } );
    video_memory[80][136] = uint_cast( bgr555_type { .green = 31 } );
    video_memory[96][120] = uint_cast( bgr555_type { .blue = 31 } );
    
    while ( true ) {}
    __builtin_unreachable();
}
```

# About

gba-plusplus is a light-weight C++ abstraction of the Game Boy Advance hardware.

* Hardware tested
* Assembler inspected
* Optimized for `-Og` and `-O3`
* C++17
* Both GCC and Clang compatible
* Compatible with [Tonclib](https://www.coranac.com/man/tonclib/main.htm) and [libgba](https://github.com/devkitPro/libgba)

## *NOT* a game engine

We make close-to-zero assumptions about the type of GBA game you are making.

## Zero tools

We do not restrict you to use any particular file formats or force you to use any additional tools.

## Explicit

The API is verbose and hides as little as possible.

Register names match the familiar documentation.

We respect the programmer, the code you write to shoot yourself in the foot will read like code that is shooting you in the foot.

# Extensions

The `gba/ext/` headers provide features outside of the core GBA hardware.

Some of these may depend on external libraries, such as [agbabi](https://github.com/felixjones/agbabi).

# In-development

We welcome all forms of feedback in the form of GitHub issues. The API will change when necessary, but don't worry all releases will be archived.
