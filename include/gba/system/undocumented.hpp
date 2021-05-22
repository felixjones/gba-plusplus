#ifndef GBAXX_SYSTEM_UNDOCUMENTED_HPP
#define GBAXX_SYSTEM_UNDOCUMENTED_HPP

#include <gba/types/int_type.hpp>

namespace gba {
namespace undocumented {

struct post_flag {
    bool raised : 1;
    uint8 : 7;
};

static_assert( sizeof( post_flag ) == 1, "post_flag must be tightly packed" );

enum class halt_control : uint8 {
    halt = 0,
    stop = 0x80
};

static_assert( sizeof( halt_control ) == 1, "halt_control must be sized 1" );

enum class object_center : uint8 {
    unknown = 0xff
};

static_assert( sizeof( object_center ) == 1, "object_center must be sized 1" );

struct memory_map {
    bool swam_ram_and_bios : 1;
    uint32 : 4;
    bool enable_ewram : 1;
    uint32 : 18;
    uint32 waitstates : 4;
    uint32 : 4;
};

static_assert( sizeof( memory_map ) == 4, "memory_map must be tightly packed" );

} // undocumented
} // gba

#endif // define GBAXX_SYSTEM_UNDOCUMENTED_HPP
