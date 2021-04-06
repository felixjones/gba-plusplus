#ifndef GBAXX_ALLOCATOR_MODE4_HPP
#define GBAXX_ALLOCATOR_MODE4_HPP

#include <gba/allocator/object_tile.hpp>
#include <gba/allocator/vram.hpp>

namespace gba {
namespace allocator {

template <>
struct mode<4> {

using object = object_tile<16, 0x6014000, 0x4000>;

};

} // allocator
} // gba

#endif // define GBAXX_ALLOCATOR_MODE4_HPP
