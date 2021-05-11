#ifndef GBAXX_EXT_AGBABI_COROUTINE_HPP
#define GBAXX_EXT_AGBABI_COROUTINE_HPP
#if defined( __agb_abi )

#include <gba/ext/agbabi/fiber.hpp>
#include <gba/ext/agbabi/pull_coroutine.hpp>
#include <gba/ext/agbabi/push_coroutine.hpp>

namespace gba {
namespace agbabi {

template <typename Type>
struct coroutine {
    using pull_type = pull_coroutine<Type>;
    using push_type = push_coroutine<Type>;
};

template <>
struct coroutine<void> {
    using pull_type = fiber;
    using push_type = fiber;
};

} // agbabi
} // gba

#endif // __agb_abi
#endif // define GBAXX_EXT_AGBABI_COROUTINE_HPP
