#ifndef GBAXX_TYPES_MATRIX_HPP
#define GBAXX_TYPES_MATRIX_HPP

#include <tuple>

#include <gba/types/vector.hpp>

namespace gba {
namespace detail {

template <unsigned N, typename... Ts>
using vargs_type = typename std::tuple_element<N, std::tuple<Ts...>>::type;

} // detail

template <unsigned C, unsigned R, typename... Ts>
struct mat {};

} // gba

#include <gba/types/matrix/mat2x2.hpp>
#include <gba/types/matrix/mat3x2.hpp>
#include <gba/types/matrix/mat3x3.hpp>
#include <gba/types/matrix/mat4x4.hpp>

#endif // define GBAXX_TYPES_MATRIX_HPP
