#ifndef GBAXX_BOOL_HPP
#define GBAXX_BOOL_HPP

#include <type_traits>

#include <gba/bool_type.hpp>

namespace gba {

// Will use native bool if possible
using bool8 = typename std::conditional<sizeof( bool ) == 1, bool, bool_type<8>>::type;
using bool16 = typename std::conditional<sizeof( bool ) == 2, bool, bool_type<16>>::type;
using bool32 = typename std::conditional<sizeof( bool ) == 4, bool, bool_type<32>>::type;
using bool64 = typename std::conditional<sizeof( bool ) == 8, bool, bool_type<64>>::type;

} // gba

#endif // define GBAXX_BOOL_HPP
