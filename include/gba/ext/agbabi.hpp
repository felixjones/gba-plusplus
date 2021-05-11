#ifndef GBAXX_EXT_AGBABI_HPP
#define GBAXX_EXT_AGBABI_HPP

#if defined( __agb_abi )

#include <gba/ext/agbabi/coroutine.hpp>
#include <gba/ext/agbabi/fiber.hpp>
#include <gba/ext/agbabi/irq_handlers.hpp>
#include <gba/ext/agbabi/math.hpp>
#include <gba/ext/agbabi/memcpy.hpp>
#include <gba/ext/agbabi/pull_coroutine.hpp>
#include <gba/ext/agbabi/push_coroutine.hpp>

#else
#error __agb_abi not defined
#endif

#endif // define GBAXX_AGBABI_HPP
