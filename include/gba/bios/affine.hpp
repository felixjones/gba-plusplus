#ifndef GBAXX_BIOS_AFFINE_HPP
#define GBAXX_BIOS_AFFINE_HPP

#include <tuple>

#include <gba/bios/swi.hpp>

namespace gba {
namespace bios {

/*[[gnu::always_inline]]
inline void obj_affine_set() noexcept {
    swi<2, void()>::call();
}*/

} // bios
} // gba

#endif // define GBAXX_BIOS_AFFINE_HPP
