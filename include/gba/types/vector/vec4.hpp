#ifndef GBAXX_TYPES_VECTOR_VEC4_HPP
#define GBAXX_TYPES_VECTOR_VEC4_HPP

#include <gba/types/vector.hpp>

namespace gba {

template <typename T>
struct vec<4, T> {
    constexpr vec() noexcept : x { 0 }, y { 0 }, z { 0 }, w { 0 } {}

    template <typename S>
    explicit constexpr vec( const S& s ) noexcept : x { s }, y { s }, z { s }, w { s } {}

    template <typename X, typename Y, typename Z, typename W>
    constexpr vec( const X& x, const Y& y, const Z& z, const W& w ) noexcept : x { x }, y { y }, z { z }, w { w } {}

    template <typename O>
    constexpr vec( const vec<4, O>& o ) noexcept : x { o.x }, y { o.y }, z { o.z }, w { o.w } {}

    template <typename O>
    explicit constexpr vec( const vec<2, O>& o ) noexcept : x { o.x }, y { o.y }, z {}, w {} {}

    template <typename O>
    explicit constexpr vec( const vec<3, O>& o ) noexcept : x { o.x }, y { o.y }, z { o.z }, w {} {}

    // -- Boolean operators --

    template <typename O>
    constexpr bool operator ==( const vec<4, O>& o ) const noexcept {
        return x == o.x && y == o.y && z == o.z && w == o.w;
    }

    template <typename O>
    constexpr bool operator !=( const vec<4, O>& o ) const noexcept {
        return x != o.x || y != o.y || z != o.z || w != o.w;
    }

    T x, y, z, w;
};

template <typename T>
using vec4 = vec<4, T>;

} // gba

#endif // define GBAXX_TYPES_VECTOR_VEC4_HPP
