#ifndef GBAXX_TYPES_MATRIX_MAT2X2_HPP
#define GBAXX_TYPES_MATRIX_MAT2X2_HPP

#include <gba/types/matrix.hpp>

namespace gba {

template <typename... Ts>
struct mat<2, 2, Ts...> {
    using column0_type = typename gba::vec<2, typename detail::vargs_type<0, Ts...>>;
    using column1_type = typename gba::vec<2, typename detail::vargs_type<1, Ts...>>;

    constexpr mat() noexcept : column0 { 1, 0 }, column1 { 0, 1 } {}

    template <typename S>
    explicit constexpr mat( const S& s ) noexcept : column0 { s, 0 }, column1 { 0, s } {}

    template <typename A, typename B, typename C, typename D>
    constexpr mat( const A& a, const B& b, const C& c, const D& d ) noexcept : column0 { a, b }, column1 { c, d } {}

    template <typename C0, typename C1>
    constexpr mat( const vec<2, C0>& c0, const vec<2, C1>& c1 ) noexcept : column0 { c0 }, column1 { c1 } {}

    template <typename... Os>
    constexpr mat( const mat<2, 2, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<3, 2, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<2, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<3, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<4, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<3, 4, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<4, 4, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 } {}

    // -- Unary updatable operators --

    template <typename... Os>
    constexpr auto& operator =( const mat<2, 2, Os...>& o) noexcept {
        column0 = o.column0;
        column1 = o.column1;
        return *this;
    }

    template <typename... Os>
    constexpr auto& operator *=( const mat<2, 2, Os...>& o) noexcept {
        return *this = *this * o;
    }

    // -- Binary arithmetic operators --

    template <typename... Os>
    constexpr auto operator *( const mat<2, 2, Os...>& o ) const noexcept {
        return mat<2, 2, Os...> {
            column0.x * o.column0.x + column1.x * o.column0.y,
            column0.y * o.column0.x + column1.y * o.column0.y,
            column0.x * o.column1.x + column1.x * o.column1.y,
            column0.y * o.column1.x + column1.y * o.column1.y
        };
    }

    template <typename... Os>
    constexpr auto operator *( const mat<3, 2, Os...>& o ) const noexcept {
        return mat<3, 2, Os...> {
            column0.x * o.column0.x + column1.x * o.column0.y,
            column0.y * o.column0.x + column1.y * o.column0.y,
            column0.x * o.column1.x + column1.x * o.column1.y,
            column0.y * o.column1.x + column1.y * o.column1.y,
            column0.x * o.column2.x + column1.x * o.column2.y,
            column0.y * o.column2.x + column1.y * o.column2.y
        };
    }

    template <typename... Os>
    constexpr auto operator *( const mat<4, 2, Os...>& o ) const noexcept {
        return mat<4, 2, Os...> {
            column0.x * o.column0.x + column1.x * o.column0.y,
            column0.y * o.column0.x + column1.y * o.column0.y,
            column0.x * o.column1.x + column1.x * o.column1.y,
            column0.y * o.column1.x + column1.y * o.column1.y,
            column0.x * o.column2.x + column1.x * o.column2.y,
            column0.y * o.column2.x + column1.y * o.column2.y,
            column0.x * o.column3.x + column1.x * o.column3.y,
            column0.y * o.column3.x + column1.y * o.column3.y
        };
    }

    // -- Boolean operators --

    template <typename... Os>
    constexpr bool operator ==( const mat<2, 2, Os...>& o ) const noexcept {
        return column0 == o.column0 && column1 == o.column1;
    }

    template <typename... Os>
    constexpr bool operator !=( const mat<2, 2, Os...>& o ) const noexcept {
        return column0 != o.column0 || column1 != o.column1;
    }

    column0_type column0;
    column1_type column1;
};

template <typename Ts>
using mat2x2 = mat<2, 2, Ts, Ts>;

template <typename Ts>
using mat2 = mat2x2<Ts>;

} // gba

#endif // define GBAXX_TYPES_MATRIX_MAT2X2_HPP
