#ifndef GBAXX_EXT_AGBABI_PULL_COROUTINE_HPP
#define GBAXX_EXT_AGBABI_PULL_COROUTINE_HPP
#if defined( __agb_abi )

#include <gba/ext/agbabi/fiber.hpp>

namespace gba {
namespace agbabi {

template <typename Type>
class push_coroutine;

template <typename Type>
class pull_coroutine {
private:
    using value_type = Type;

    class push_type {
        friend pull_coroutine;
    public:
        push_type( pull_coroutine * const pull ) noexcept : m_pull { pull } {}

        push_type& operator ()( const value_type& value ) noexcept {
            m_value.emplace( value );
            __agbabi_swapcontext( &m_pull->m_context, &m_pull->m_link );
            return *this;
        }

        push_type& operator ()( value_type&& value ) noexcept {
            m_value.emplace( std::move( value ) );
            __agbabi_swapcontext( &m_pull->m_context, &m_pull->m_link );
            return *this;
        }
    private:
        push_type( push_type&& other ) noexcept : m_pull { other.m_pull }, m_value( std::move( other.m_value ) ) {
            other.m_pull = nullptr;
            other.m_value.reset();
        }

        pull_coroutine * m_pull;
        std::optional<value_type> m_value;
    };

    using function_type = std::function<void( push_type& )>;

    struct sentinel {};

    class iterator {
    public:
        using value_type = typename pull_coroutine::value_type;
        using difference_type = std::ptrdiff_t;
        using reference_type = value_type&;
        using pointer_type = value_type *;

        iterator() = default;
        iterator( iterator& ) = default;
        iterator( iterator&& ) = default;
        iterator& operator =( iterator& ) = default;

        iterator( pull_coroutine& pull ) noexcept : m_pull { &pull } {
            ( *m_pull )();
        }

        [[nodiscard]]
        bool operator ==( sentinel ) const noexcept {
            return !( *m_pull );
        }

        [[nodiscard]]
        bool operator !=( sentinel ) const noexcept {
            return *m_pull;
        }

        [[nodiscard]]
        auto operator *() const noexcept {
            return m_pull->get();
        }

        iterator& operator ++() noexcept {
            ( *m_pull )();
            return *this;
        }

        iterator& operator ++( int ) noexcept {
            ( *m_pull )();
            return *this;
        }

    private:
        pull_coroutine * const m_pull;
    };
public:
    pull_coroutine( const pull_coroutine& ) = delete;
    pull_coroutine& operator =( const pull_coroutine& ) = delete;

    pull_coroutine( const stack_t& stack, function_type&& function ) noexcept : m_context { &m_link, stack, {} } {
        // Allocate space in our stack for control object and call function
        m_push = detail::stack_emplace<push_type>( m_context.uc_stack, this );
        auto * const functionOnStack = detail::stack_put( m_context.uc_stack, function );
        const auto callFunc = reinterpret_cast<void( * )( void )>( call );

        __agbabi_makecontext( &m_context, callFunc, 2, std::ref( *m_push ), functionOnStack );
        m_start = m_context.uc_mcontext;
    }

    pull_coroutine( pull_coroutine&& other ) noexcept : m_context { other.m_context }, m_link { other.m_link }, m_start { other.m_start }, m_push { other.m_push } {
        other.m_context = {};
        other.m_link = {};
        other.m_start = {};
        other.m_push = nullptr;
        m_push->m_pull = this;
        detail::stack_set_link( m_context.uc_stack, m_link );
    }

    ~pull_coroutine() noexcept {
        if ( m_push ) {
            m_push->~push_type();
        }
    }

    pull_coroutine& operator ()() noexcept {
        __agbabi_swapcontext( &m_link, &m_context );
        return *this;
    }

    [[nodiscard]]
    operator bool() const noexcept {
        return m_push->m_value.has_value();
    }

    [[nodiscard]]
    const value_type& get() const noexcept {
        return m_push->m_value.value();
    }

    [[nodiscard]]
    iterator begin() noexcept {
        return iterator( *this );
    }

    [[nodiscard]]
    sentinel end() const noexcept {
        return {};
    }
private:
    void reset() noexcept {
        m_context.uc_mcontext = m_start;
    }

    static void call( push_type& push, function_type * const function ) noexcept {
        ( *function )( push );
        push.m_value.reset();
        push.m_pull->reset();
    }

    ucontext_t m_context;
    ucontext_t m_link;
    mcontext_t m_start;
    push_type * m_push;
};

} // agbabi
} // gba

#endif // __agb_abi
#endif // define GBAXX_EXT_AGBABI_PULL_COROUTINE_HPP
