#ifndef GBAXX_TYPES_SCREEN_SIZE_HPP
#define GBAXX_TYPES_SCREEN_SIZE_HPP

#include <gba/types/int_type.hpp>

namespace gba {

enum class screen_size : uint16 {
    regular_32x32 = 0,
    regular_64x32 = 1,
    regular_32x64 = 2,
    regular_64x64 = 3,
    affine_16x16 = 0,
    affine_32x32 = 1,
    affine_64x64 = 2,
    affine_128x128 = 3
};

enum class screen_size_regular : uint16 {
    _32x32 = static_cast<uint16>( screen_size::regular_32x32 ),
    _64x32 = static_cast<uint16>( screen_size::regular_64x32 ),
    _32x64 = static_cast<uint16>( screen_size::regular_32x64 ),
    _64x64 = static_cast<uint16>( screen_size::regular_64x64 )
};

constexpr uint32 screen_count( const screen_size_regular size ) noexcept {
    switch ( size ) {
        case screen_size_regular::_32x32:
            return 1;
        case screen_size_regular::_64x32:
        case screen_size_regular::_32x64:
            return 2;
        case screen_size_regular::_64x64:
            return 3;
        default:
            return 0;
    }
}

enum class screen_size_affine : uint16 {
    _16x16 = static_cast<uint16>( screen_size::affine_16x16 ),
    _32x32 = static_cast<uint16>( screen_size::affine_32x32 ),
    _64x64 = static_cast<uint16>( screen_size::affine_64x64 ),
    _128x128 = static_cast<uint16>( screen_size::affine_128x128 )
};

constexpr uint32 screen_count( const screen_size_affine size ) noexcept {
    switch ( size ) {
        case screen_size_affine::_16x16:
        case screen_size_affine::_32x32:
            return 1;
        case screen_size_affine::_64x64:
            return 2;
        case screen_size_affine::_128x128:
            return 8;
        default:
            return 0;
    }
}

} // gba

#endif // define GBAXX_TYPES_SCREEN_SIZE_HPP
