#ifndef GBAXX_INT_HPP
#define GBAXX_INT_HPP

#include <cstdint>

#include <gba/packed_int.hpp>

namespace gba {

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint24 = packed_int<uint8, 3>;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using int8 = std::int8_t;
using int16 = std::int16_t;
using int24 = packed_int<int8, 3>;
using int32 = std::int32_t;
using int64 = std::int64_t;

} // gba

#endif // define GBAXX_INT_HPP
