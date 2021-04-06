#ifndef GBAXX_ALLOCATOR_MODE5_HPP
#define GBAXX_ALLOCATOR_MODE5_HPP

#include <gba/allocator/object_tile.hpp>
#include <gba/allocator/vram.hpp>

namespace gba {
namespace allocator {

template <>
struct mode<5> {

using object = object_tile<16, 0x6014000, 0x4000>;

};

} // allocator
} // gba

#endif // define GBAXX_ALLOCATOR_MODE5_HPP
