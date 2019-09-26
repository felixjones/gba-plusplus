#ifndef GBAXX_BOOL_HPP
#define GBAXX_BOOL_HPP

#include <gba/sized_bool.hpp>

namespace gba {

// Will use native bool if possible
using bool8 = typename std::conditional<sizeof( bool ) == 1, bool, sized_bool<1>>::type;
using bool16 = typename std::conditional<sizeof( bool ) == 2, bool, sized_bool<2>>::type;
using bool32 = typename std::conditional<sizeof( bool ) == 4, bool, sized_bool<4>>::type;
using bool64 = typename std::conditional<sizeof( bool ) == 8, bool, sized_bool<8>>::type;

} // gba

#endif // define GBAXX_BOOL_HPP
