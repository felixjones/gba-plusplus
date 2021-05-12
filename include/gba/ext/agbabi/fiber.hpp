#ifndef GBAXX_EXT_AGBABI_FIBER_HPP
#define GBAXX_EXT_AGBABI_FIBER_HPP
#if defined( __agb_abi )

#include <sys/ucontext.h>

extern "C" {

int __agbabi_getcontext( ucontext_t * );
int __agbabi_setcontext( const ucontext_t * ) ;
void __agbabi_makecontext( ucontext_t *, void ( * )( void ), int, ... );
int __agbabi_swapcontext( ucontext_t *, const ucontext_t * );

}

namespace gba {
namespace agbabi {
namespace detail {

template <typename Type, typename... Args>
Type * stack_emplace( stack_t& stack, Args... args ) noexcept {
    auto * stackEnd = reinterpret_cast<char *>( stack.ss_sp ) + stack.ss_size;
    stackEnd -= sizeof( Type );
    stack.ss_size -= sizeof( Type );
    return new ( stackEnd ) Type( std::forward<Args>( args )... );
}

template <typename Type>
Type * stack_put( stack_t& stack, const Type& type ) noexcept {
    auto * stackEnd = reinterpret_cast<char *>( stack.ss_sp ) + stack.ss_size;
    stackEnd -= sizeof( type );
    stack.ss_size -= sizeof( type );
    return new ( stackEnd ) Type( type );
}

inline void stack_set_link( stack_t& stack, const ucontext_t& link ) noexcept {
    // re-write pointer to link context set by __agbabi_makecontext
    auto * stackEnd = reinterpret_cast<const ucontext_t **>( reinterpret_cast<char *>( stack.ss_sp ) + stack.ss_size );
    stackEnd -= 1;
    *stackEnd = &link;
}

} // detail

class fiber {
private:
    class yield_type {
        friend fiber;
    public:
        yield_type( fiber * owner ) noexcept : m_owner { owner }, m_hasYielded { false } {}

        void operator ()() noexcept {
            m_hasYielded = true;
            __agbabi_swapcontext( &m_owner->m_context, &m_owner->m_link );
        }

    private:
        yield_type( yield_type&& other ) noexcept : m_owner { other.m_owner }, m_hasYielded { other.m_hasYielded } {
            other.m_owner = nullptr;
        }

        fiber * m_owner;
        bool m_hasYielded;
    };

    using function_type = std::function<void( yield_type& )>;
public:
    fiber( const fiber& ) = delete;
    fiber& operator =( const fiber& ) = delete;

    fiber( const stack_t& stack, function_type&& function ) noexcept : m_context { &m_link, stack, {} } {
        // Allocate space in our stack for control object and call function
        m_yield = detail::stack_emplace<yield_type>( m_context.uc_stack, this );
        auto * const functionOnStack = detail::stack_put( m_context.uc_stack, function );
        const auto callFunc = reinterpret_cast<void( * )( void )>( call );

        __agbabi_makecontext( &m_context, callFunc, 2, std::ref( *m_yield ), functionOnStack );
        m_start = m_context.uc_mcontext;
    }

    fiber( fiber&& other ) noexcept : m_context { other.m_context }, m_link { other.m_link }, m_start { other.m_start }, m_yield { other.m_yield } {
        other.m_context = {};
        other.m_link = {};
        other.m_start = {};
        other.m_yield = nullptr;
        m_yield->m_owner = this;
        detail::stack_set_link( m_context.uc_stack, m_link );
    }

    ~fiber() noexcept {
        if ( m_yield ) {
            m_yield->~yield_type();
        }
    }

    fiber& operator ()() noexcept {
        m_yield->m_hasYielded = false;
        __agbabi_swapcontext( &m_link, &m_context );
        return *this;
    }

    [[nodiscard]]
    operator bool() const noexcept {
        return m_yield->m_hasYielded;
    }
private:
    void reset() noexcept {
        m_context.uc_mcontext = m_start;
    }

    static void call( yield_type& yield, function_type * const function ) noexcept {
        ( *function )( yield );
        yield.m_owner->reset();
    }

    ucontext_t m_context;
    ucontext_t m_link;
    mcontext_t m_start;
    yield_type * m_yield;
};

} // agbabi
} // gba

#endif // __agb_abi
#endif // define GBAXX_EXT_AGBABI_FIBER_HPP
