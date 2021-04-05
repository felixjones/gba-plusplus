#ifndef GBAXX_TYPES_VECTOR_VEC2_HPP
#define GBAXX_TYPES_VECTOR_VEC2_HPP

#include <gba/types/vector.hpp>

namespace gba {

template <typename T>
struct vec<2, T> {
    using value_type = T;

    constexpr vec() noexcept : x { 0 }, y { 0 } {}

    template <typename S>
    explicit constexpr vec( const S& s ) noexcept : x { s }, y { s } {}

    template <typename X, typename Y>
    constexpr vec( const X& x, const Y& y ) noexcept : x { x }, y { y } {}

    template <typename O>
    constexpr vec( const vec<2, O>& o ) noexcept : x { o.x }, y { o.y } {}

    template <typename O>
    explicit constexpr vec( const vec<3, O>& o ) noexcept : x { o.x }, y { o.y } {}

    template <typename O>
    explicit constexpr vec( const vec<4, O>& o ) noexcept : x { o.x }, y { o.y } {}

    // -- Boolean operators --

    template <typename O>
    constexpr bool operator ==( const vec<2, O>& o ) const noexcept {
        return x == o.x && y == o.y;
    }

    template <typename O>
    constexpr bool operator !=( const vec<2, O>& o ) const noexcept {
        return x != o.x || y != o.y;
    }

    value_type x, y;
};

template <typename T>
using vec2 = vec<2, T>;

} // gba

#endif // define GBAXX_TYPES_VECTOR_VEC2_HPP
