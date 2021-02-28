#ifndef GBAXX_TYPES_MATRIX_MAT3X3_HPP
#define GBAXX_TYPES_MATRIX_MAT3X3_HPP

#include <gba/types/matrix.hpp>

namespace gba {

template <typename... Ts>
struct mat<3, 3, Ts...> {
    using column0_type = typename gba::vec<3, typename detail::vargs_type<0, Ts...>>;
    using column1_type = typename gba::vec<3, typename detail::vargs_type<1, Ts...>>;
    using column2_type = typename gba::vec<3, typename detail::vargs_type<2, Ts...>>;

    constexpr mat() noexcept : column0 { 1, 0, 0 }, column1 { 0, 1, 0 }, column2 { 0, 0, 1 } {}

    template <typename S>
    explicit constexpr mat( const S& s ) noexcept : column0 { s, 0, 0 }, column1 { 0, s, 0 }, column2 { 0, 0, s } {}

    template <typename M00, typename M01, typename M02,
            typename M10, typename M11, typename M12,
            typename M20, typename M21, typename M22>
    constexpr mat( const M00& m00, const M01& m01, const M02& m02,
                   const M10& m10, const M11& m11, const M12& m12,
                   const M20& m20, const M21& m21, const M22& m22 ) noexcept :
                   column0 { m00, m01, m02 }, column1 { m10, m11, m12 }, column2 { m20, m21, m22 } {}

    template <typename C0, typename C1, typename C2>
    constexpr mat( const vec<3, C0>& c0, const vec<3, C1>& c1, const vec<3, C2>& c2 ) noexcept : column0 { c0 }, column1 { c1 }, column2 { c2 } {}

    template <typename... Os>
    constexpr mat( const mat<3, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<2, 2, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 {} {}

    template <typename... Os>
    explicit constexpr mat( const mat<3, 2, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<2, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 {} {}

    template <typename... Os>
    explicit constexpr mat( const mat<4, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<3, 4, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<4, 4, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 } {}

    // -- Unary updatable operators --

    template <typename... Os>
    constexpr auto& operator =( const mat<3, 3, Os...>& o) noexcept {
        column0 = o.column0;
        column1 = o.column1;
        column2 = o.column2;
        return *this;
    }

    template <typename... Os>
    constexpr auto& operator *=( const mat<3, 3, Os...>& o) noexcept {
        return *this = *this * o;
    }

    // -- Binary arithmetic operators --

    template <typename... Os>
    constexpr auto operator *( const mat<3, 3, Os...>& o ) const noexcept {
        const auto& srcA00 = column0.x;
        const auto& srcA01 = column0.y;
        const auto& srcA02 = column0.z;
        const auto& srcA10 = column1.x;
        const auto& srcA11 = column1.y;
        const auto& srcA12 = column1.z;
        const auto& srcA20 = column2.x;
        const auto& srcA21 = column2.y;
        const auto& srcA22 = column2.z;

        const auto& srcB00 = o.column0.x;
        const auto& srcB01 = o.column0.y;
        const auto& srcB02 = o.column0.z;
        const auto& srcB10 = o.column1.x;
        const auto& srcB11 = o.column1.y;
        const auto& srcB12 = o.column1.z;
        const auto& srcB20 = o.column2.x;
        const auto& srcB21 = o.column2.y;
        const auto& srcB22 = o.column2.z;

        return mat<3, 3, Os...> {
            srcA00 * srcB00 + srcA10 * srcB01 + srcA20 * srcB02,
            srcA01 * srcB00 + srcA11 * srcB01 + srcA21 * srcB02,
            srcA02 * srcB00 + srcA12 * srcB01 + srcA22 * srcB02,
            srcA00 * srcB10 + srcA10 * srcB11 + srcA20 * srcB12,
            srcA01 * srcB10 + srcA11 * srcB11 + srcA21 * srcB12,
            srcA02 * srcB10 + srcA12 * srcB11 + srcA22 * srcB12,
            srcA00 * srcB20 + srcA10 * srcB21 + srcA20 * srcB22,
            srcA01 * srcB20 + srcA11 * srcB21 + srcA21 * srcB22,
            srcA02 * srcB20 + srcA12 * srcB21 + srcA22 * srcB22
        };
    }

    template <typename... Os>
    constexpr auto operator *( const mat<2, 3, Os...>& o ) const noexcept {
        return mat<2, 3, Os...> {
            column0.x * o.column0.x + column1.x * o.column0.y + column2.x * o.column0.z,
            column0.y * o.column0.x + column1.y * o.column0.y + column2.y * o.column0.z,
            column0.z * o.column0.x + column1.z * o.column0.y + column2.z * o.column0.z,
            column0.x * o.column1.x + column1.x * o.column1.y + column2.x * o.column1.z,
            column0.y * o.column1.x + column1.y * o.column1.y + column2.y * o.column1.z,
            column0.z * o.column1.x + column1.z * o.column1.y + column2.z * o.column1.z
        };
    }

    template <typename... Os>
    constexpr auto operator *( const mat<4, 3, Os...>& o ) const noexcept {
        return mat<4, 3, Os...> {
            column0.x * o.column0.x + column1.x * o.column0.y + column2.x * o.column0.z,
            column0.y * o.column0.x + column1.y * o.column0.y + column2.y * o.column0.z,
            column0.z * o.column0.x + column1.z * o.column0.y + column2.z * o.column0.z,
            column0.x * o.column1.x + column1.x * o.column1.y + column2.x * o.column1.z,
            column0.y * o.column1.x + column1.y * o.column1.y + column2.y * o.column1.z,
            column0.z * o.column1.x + column1.z * o.column1.y + column2.z * o.column1.z,
            column0.x * o.column2.x + column1.x * o.column2.y + column2.x * o.column2.z,
            column0.y * o.column2.x + column1.y * o.column2.y + column2.y * o.column2.z,
            column0.z * o.column2.x + column1.z * o.column2.y + column2.z * o.column2.z,
            column0.x * o.column3.x + column1.x * o.column3.y + column2.x * o.column3.z,
            column0.y * o.column3.x + column1.y * o.column3.y + column2.y * o.column3.z,
            column0.z * o.column3.x + column1.z * o.column3.y + column2.z * o.column3.z
        };
    }

    // -- Boolean operators --

    template <typename... Os>
    constexpr bool operator ==( const mat<3, 3, Os...>& o ) const noexcept {
        return column0 == o.column0 && column1 == o.column1 && column2 == o.column2;
    }

    template <typename... Os>
    constexpr bool operator !=( const mat<3, 3, Os...>& o ) const noexcept {
        return column0 != o.column0 || column1 != o.column1 || column2 != o.column2;
    }

    column0_type column0;
    column1_type column1;
    column2_type column2;
};

template <typename Ts>
using mat3x3 = mat<3, 3, Ts, Ts, Ts>;

template <typename Ts>
using mat3 = mat3x3<Ts>;

} // gba

#endif // define GBAXX_TYPES_MATRIX_MAT3X3_HPP
