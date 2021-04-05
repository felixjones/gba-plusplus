#ifndef GBAXX_ALLOCATOR_BITSET_HPP
#define GBAXX_ALLOCATOR_BITSET_HPP

#include <gba/types/int_type.hpp>

namespace gba {
namespace allocator {

template <unsigned Pages>
class bitset {
private:
    uint32  m_bitset[Pages];
};

} // allocator
} // gba

#endif // define GBAXX_ALLOCATOR_BITSET_HPP
