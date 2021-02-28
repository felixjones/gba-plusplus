#ifndef GBAXX_TYPES_MATRIX_MAT4X4_HPP
#define GBAXX_TYPES_MATRIX_MAT4X4_HPP

#include <gba/types/matrix.hpp>

namespace gba {

template <typename... Ts>
struct mat<4, 4, Ts...> {
    using column0_type = typename gba::vec<4, typename detail::vargs_type<0, Ts...>>;
    using column1_type = typename gba::vec<4, typename detail::vargs_type<1, Ts...>>;
    using column2_type = typename gba::vec<4, typename detail::vargs_type<2, Ts...>>;
    using column3_type = typename gba::vec<4, typename detail::vargs_type<3, Ts...>>;

    constexpr mat() noexcept : column0 { 1, 0, 0, 0 }, column1 { 0, 1, 0, 0 }, column2 { 0, 0, 1, 0 }, column3 { 0, 0, 0, 1 } {}

    template <typename S>
    explicit constexpr mat( const S& s ) noexcept : column0 { s, 0, 0, 0 }, column1 { 0, s, 0, 0 }, column2 { 0, 0, s, 0 }, column3 { 0, 0, 0, s } {}

    template <typename M00, typename M01, typename M02, typename M03,
            typename M10, typename M11, typename M12, typename M13,
            typename M20, typename M21, typename M22, typename M23,
            typename M30, typename M31, typename M32, typename M33>
    constexpr mat( const M00& m00, const M01& m01, const M02& m02, const M03& m03,
                   const M10& m10, const M11& m11, const M12& m12, const M13& m13,
                   const M20& m20, const M21& m21, const M22& m22, const M23& m23,
                   const M30& m30, const M31& m31, const M32& m32, const M33& m33 ) noexcept :
                   column0 { m00, m01, m02, m03 }, column1 { m10, m11, m12, m13 }, column2 { m20, m21, m22, m23 }, column3 { m30, m31, m32, m33 } {}

    template <typename C0, typename C1, typename C2, typename C3>
    constexpr mat( const vec<4, C0>& c0, const vec<4, C1>& c1, const vec<4, C2>& c2, const vec<4, C3>& c3 ) noexcept : column0 { c0 }, column1 { c1 }, column2 { c2 }, column3 { c3 } {}

    template <typename... Os>
    constexpr mat( const mat<4, 4, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 }, column3 { o.column3 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<2, 2, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 {}, column3 {} {}

    template <typename... Os>
    explicit constexpr mat( const mat<3, 2, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 }, column3 {} {}

    template <typename... Os>
    explicit constexpr mat( const mat<2, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 {}, column3 {} {}

    template <typename... Os>
    explicit constexpr mat( const mat<3, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 }, column3 {} {}

    template <typename... Os>
    explicit constexpr mat( const mat<4, 3, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 }, column3 { o.column3 } {}

    template <typename... Os>
    explicit constexpr mat( const mat<3, 4, Os...>& o ) noexcept : column0 { o.column0 }, column1 { o.column1 }, column2 { o.column2 }, column3 {} {}

    // -- Unary updatable operators --

    template <typename... Os>
    constexpr auto& operator =( const mat<4, 4, Os...>& o) noexcept {
        column0 = o.column0;
        column1 = o.column1;
        column2 = o.column2;
        column3 = o.column3;
        return *this;
    }

    template <typename... Os>
    constexpr auto& operator *=( const mat<4, 4, Os...>& o) noexcept {
        return *this = *this * o;
    }

    // -- Binary arithmetic operators --

    template <typename... Os>
    constexpr auto operator *( const mat<4, 4, Os...>& o ) const noexcept {
        const auto& srcA00 = column0.x;
        const auto& srcA01 = column0.y;
        const auto& srcA02 = column0.z;
        const auto& srcA03 = column0.w;
        const auto& srcA10 = column1.x;
        const auto& srcA11 = column1.y;
        const auto& srcA12 = column1.z;
        const auto& srcA13 = column1.w;
        const auto& srcA20 = column2.x;
        const auto& srcA21 = column2.y;
        const auto& srcA22 = column2.z;
        const auto& srcA23 = column2.w;
        const auto& srcA30 = column3.x;
        const auto& srcA31 = column3.y;
        const auto& srcA32 = column3.z;
        const auto& srcA33 = column3.w;

        const auto& srcB00 = o.column0.x;
        const auto& srcB01 = o.column0.y;
        const auto& srcB02 = o.column0.z;
        const auto& srcB03 = o.column0.w;
        const auto& srcB10 = o.column1.x;
        const auto& srcB11 = o.column1.y;
        const auto& srcB12 = o.column1.z;
        const auto& srcB13 = o.column1.w;
        const auto& srcB20 = o.column2.x;
        const auto& srcB21 = o.column2.y;
        const auto& srcB22 = o.column2.z;
        const auto& srcB23 = o.column2.w;
        const auto& srcB30 = o.column3.x;
        const auto& srcB31 = o.column3.y;
        const auto& srcB32 = o.column3.z;
        const auto& srcB33 = o.column3.w;

        return mat<4, 4, Os...> {
            srcA00 * srcB00 + srcA10 * srcB01 + srcA20 * srcB02 + srcA30 * srcB03,
            srcA01 * srcB00 + srcA11 * srcB01 + srcA21 * srcB02 + srcA31 * srcB03,
            srcA02 * srcB00 + srcA12 * srcB01 + srcA22 * srcB02 + srcA32 * srcB03,
            srcA03 * srcB00 + srcA13 * srcB01 + srcA23 * srcB02 + srcA33 * srcB03,
            srcA00 * srcB10 + srcA10 * srcB11 + srcA20 * srcB12 + srcA30 * srcB13,
            srcA01 * srcB10 + srcA11 * srcB11 + srcA21 * srcB12 + srcA31 * srcB13,
            srcA02 * srcB10 + srcA12 * srcB11 + srcA22 * srcB12 + srcA32 * srcB13,
            srcA03 * srcB10 + srcA13 * srcB11 + srcA23 * srcB12 + srcA33 * srcB13,
            srcA00 * srcB20 + srcA10 * srcB21 + srcA20 * srcB22 + srcA30 * srcB23,
            srcA01 * srcB20 + srcA11 * srcB21 + srcA21 * srcB22 + srcA31 * srcB23,
            srcA02 * srcB20 + srcA12 * srcB21 + srcA22 * srcB22 + srcA32 * srcB23,
            srcA03 * srcB20 + srcA13 * srcB21 + srcA23 * srcB22 + srcA33 * srcB23,
            srcA00 * srcB30 + srcA10 * srcB31 + srcA20 * srcB32 + srcA30 * srcB33,
            srcA01 * srcB30 + srcA11 * srcB31 + srcA21 * srcB32 + srcA31 * srcB33,
            srcA02 * srcB30 + srcA12 * srcB31 + srcA22 * srcB32 + srcA32 * srcB33,
            srcA03 * srcB30 + srcA13 * srcB31 + srcA23 * srcB32 + srcA33 * srcB33
        };
    }

    // -- Boolean operators --

    template <typename... Os>
    constexpr bool operator ==( const mat<4, 4, Os...>& o ) const noexcept {
        return column0 == o.column0 && column1 == o.column1 && column2 == o.column2 && column3 == o.column3;
    }

    template <typename... Os>
    constexpr bool operator !=( const mat<3, 3, Os...>& o ) const noexcept {
        return column0 != o.column0 || column1 != o.column1 || column2 != o.column2 || column3 != o.column3;
    }

    column0_type column0;
    column1_type column1;
    column2_type column2;
    column3_type column3;
};

template <typename Ts>
using mat4x4 = mat<4, 4, Ts, Ts, Ts, Ts>;

template <typename Ts>
using mat4 = mat4x4<Ts>;

} // gba

#endif // define GBAXX_TYPES_MATRIX_MAT4X4_HPP
