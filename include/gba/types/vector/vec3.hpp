#ifndef GBAXX_TYPES_VECTOR_VEC3_HPP
#define GBAXX_TYPES_VECTOR_VEC3_HPP

#include <gba/types/vector.hpp>

namespace gba {

template <typename T>
struct vec<3, T> {
    constexpr vec() noexcept : x { 0 }, y { 0 }, z { 0 } {}

    template <typename S>
    explicit constexpr vec( const S& s ) noexcept : x { s }, y { s }, z { s } {}

    template <typename X, typename Y, typename Z>
    constexpr vec( const X& x, const Y& y, const Z& z ) noexcept : x { x }, y { y }, z { z } {}

    template <typename O>
    constexpr vec( const vec<3, O>& o ) noexcept : x { o.x }, y { o.y }, z { o.z } {}

    template <typename O>
    explicit constexpr vec( const vec<2, O>& o ) noexcept : x { o.x }, y { o.y }, z {} {}

    template <typename O>
    explicit constexpr vec( const vec<4, O>& o ) noexcept : x { o.x }, y { o.y }, z { o.z } {}

    // -- Boolean operators --

    template <typename O>
    constexpr bool operator ==( const vec<3, O>& o ) const noexcept {
        return x == o.x && y == o.y && z == o.z;
    }

    template <typename O>
    constexpr bool operator !=( const vec<3, O>& o ) const noexcept {
        return x != o.x || y != o.y || z != o.z;
    }

    T x, y, z;
};

template <typename T>
using vec3 = vec<3, T>;

} // gba

#endif // define GBAXX_TYPES_VECTOR_VEC3_HPP
