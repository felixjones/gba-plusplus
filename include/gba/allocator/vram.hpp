#ifndef GBAXX_ALLOCATOR_VRAM_HPP
#define GBAXX_ALLOCATOR_VRAM_HPP

namespace gba {
namespace allocator {

template <unsigned Mode>
struct mode {};

} // allocator
} // gba

#include <gba/allocator/mode0.hpp>
#include <gba/allocator/mode1.hpp>
#include <gba/allocator/mode2.hpp>
#include <gba/allocator/mode3.hpp>
#include <gba/allocator/mode4.hpp>
#include <gba/allocator/mode5.hpp>

#endif // define GBAXX_ALLOCATOR_VRAM_HPP
