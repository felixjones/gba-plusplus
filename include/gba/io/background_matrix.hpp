#ifndef GBAXX_IO_BACKGROUND_MATRIX_HPP
#define GBAXX_IO_BACKGROUND_MATRIX_HPP

#include <gba/types/fixed_point.hpp>
#include <gba/types/int_type.hpp>
#include <gba/types/matrix.hpp>

namespace gba {
namespace io {

using background_mat2 = mat<2, 2, make_fixed<7, 8>, make_fixed<7, 8>>;
using background_mat3x2 = mat<3, 2, make_fixed<7, 8>, make_fixed<7, 8>, make_fixed<19, 8>>;

} // io
} // gba

#endif // define GBAXX_IO_BACKGROUND_MATRIX_HPP
