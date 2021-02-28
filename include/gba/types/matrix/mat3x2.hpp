#ifndef GBAXX_TYPES_MATRIX_MAT3X2_HPP
#define GBAXX_TYPES_MATRIX_MAT3X2_HPP

#include <gba/types/matrix.hpp>

namespace gba {

template <typename... Ts>
struct mat<3, 2, Ts...> {
    using column0_type = typename gba::vec<2, typename detail::vargs_type<0, Ts...>>;
    using column1_type = typename gba::vec<2, typename detail::vargs_type<1, Ts...>>;
    using column2_type = typename gba::vec<2, typename detail::vargs_type<2, Ts...>>;

    constexpr mat() noexcept : column0 { 1, 0 }, column1 { 0, 1 }, column2 { 0, 0 } {}

    template <typename S>
    explicit constexpr mat( const S& s ) noexcept : column0 { s, 0 }, column1 { 0, s }, column2 { 0, 0 } {}

    template <typename A, typename B, typename C, typename D, typename X, typename Y>
    constexpr mat( const A& a, const B& b, const C& c, const D& d, const X& x, const Y& y ) noexcept : column0 { a, b }, column1 { c, d }, column2 { x, y } {}

    template <typename C0, typename C1, typename C2>
    constexpr mat( const vec<2, C0>& c0, const vec<2, C1>& c1, const vec<2, C2>& c2 ) noexcept : column0 { c0 }, column1 { c1 }, column2 { c2 } {}

    template <typename... Os>
    constexpr mat( const mat<3, 2, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<2, 2, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 {} {}

    template <typename... Os>
    explicit constexpr mat( const mat<2, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 {} {}

    template <typename... Os>
    explicit constexpr mat( const mat<3, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<4, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<3, 4, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<4, 4, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 } {}

    // -- Unary updatable operators --

    template <typename... Os>
    constexpr auto& operator =( const mat<3, 2, Os...>& o) noexcept {
        column0 = o.column0;
        column1 = o.column1;
        column2 = o.column2;
        return *this;
    }

    // -- Binary arithmetic operators --

    template <typename... Os>
    constexpr auto operator *( const mat<2, 3, Os...>& o ) const noexcept {
        const auto& srcA00 = column0.x;
        const auto& srcA01 = column0.y;
        const auto& srcA10 = column1.x;
        const auto& srcA11 = column1.y;
        const auto& srcA20 = column2.x;
        const auto& srcA21 = column2.y;

        const auto& srcB00 = o.column0.x;
        const auto& srcB01 = o.column0.y;
        const auto& srcB02 = o.column0.z;
        const auto& srcB10 = o.column1.x;
        const auto& srcB11 = o.column1.y;
        const auto& srcB12 = o.column1.z;

        return mat<2, 2, Os...> {
            srcA00 * srcB00 + srcA10 * srcB01 + srcA20 * srcB02,
            srcA01 * srcB00 + srcA11 * srcB01 + srcA21 * srcB02,
            srcA00 * srcB10 + srcA10 * srcB11 + srcA20 * srcB12,
            srcA01 * srcB10 + srcA11 * srcB11 + srcA21 * srcB12
        };
    }

    template <typename... Os>
    constexpr auto operator *( const mat<3, 3, Os...>& o ) const noexcept {
        return mat<3, 2, Os...> {
            column0.x * o.column0.x + column1.x * o.column0.y + column2.x * o.column0.z,
            column0.y * o.column0.x + column1.y * o.column0.y + column2.y * o.column0.z,
            column0.x * o.column1.x + column1.x * o.column1.y + column2.x * o.column1.z,
            column0.y * o.column1.x + column1.y * o.column1.y + column2.y * o.column1.z,
            column0.x * o.column2.x + column1.x * o.column2.y + column2.x * o.column2.z,
            column0.y * o.column2.x + column1.y * o.column2.y + column2.y * o.column2.z
        };
    }

    template <typename... Os>
    constexpr auto operator *( const mat<4, 2, Os...>& o ) const noexcept {
        return mat<4, 2, Os...> {
            column0.x * o.column0.x + column1.x * o.column0.y + column2.x * o.column0.z,
            column0.y * o.column0.x + column1.y * o.column0.y + column2.y * o.column0.z,
            column0.x * o.column1.x + column1.x * o.column1.y + column2.x * o.column1.z,
            column0.y * o.column1.x + column1.y * o.column1.y + column2.y * o.column1.z,
            column0.x * o.column2.x + column1.x * o.column2.y + column2.x * o.column2.z,
            column0.y * o.column2.x + column1.y * o.column2.y + column2.y * o.column2.z,
            column0.x * o.column3.x + column1.x * o.column3.y + column2.x * o.column3.z,
            column0.y * o.column3.x + column1.y * o.column3.y + column2.y * o.column3.z
        };
    }

    // -- Boolean operators --

    template <typename... Os>
    constexpr bool operator ==( const mat<3, 2, Os...>& o ) const noexcept {
        return column0 == o.column0 && column1 == o.column1 && column2 == o.column2;
    }

    template <typename... Os>
    constexpr bool operator !=( const mat<3, 2, Os...>& o ) const noexcept {
        return column0 != o.column0 || column1 != o.column1 || column2 != o.column2;
    }

    column0_type column0;
    column1_type column1;
    column2_type column2;
};

template <typename Ts>
using mat3x2 = mat<3, 2, Ts, Ts, Ts>;

} // gba

#endif // define GBAXX_TYPES_MATRIX_MAT3X2_HPP
