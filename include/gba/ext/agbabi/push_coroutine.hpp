#ifndef GBAXX_EXT_AGBABI_PUSH_COROUTINE_HPP
#define GBAXX_EXT_AGBABI_PUSH_COROUTINE_HPP
#if defined( __agb_abi )

#include <gba/ext/agbabi/fiber.hpp>

namespace gba {
namespace agbabi {

template <typename Type>
class pull_coroutine;

template <typename Type>
class push_coroutine {
private:
    using value_type = Type;

    class pull_type {
        friend push_coroutine;
    private:
        struct sentinel {};

        class iterator {
        public:
            using value_type = typename push_coroutine::value_type;
            using difference_type = std::ptrdiff_t;
            using reference_type = value_type&;
            using pointer_type = value_type *;

            iterator() = default;
            iterator( iterator& ) = default;
            iterator( iterator&& ) = default;
            iterator& operator =( iterator& ) = default;

            iterator( pull_type& pull ) noexcept : m_pull { &pull } {
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
            pull_type * const m_pull;
        };
    public:
        const value_type& operator ()() noexcept {
            m_value.reset();
            __agbabi_swapcontext( &m_push->m_context, &m_push->m_link );
            return m_value.value();
        }

        [[nodiscard]]
        operator bool() const noexcept {
            return m_value.has_value();
        }

        [[nodiscard]]
        const value_type& get() const noexcept {
            return m_value.value();
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
        pull_type( push_coroutine * const push ) noexcept : m_push { push } {}

        pull_type( pull_type&& other ) noexcept : m_push { other.m_push }, m_value( std::move( other.m_value ) ) {
            other.m_push = nullptr;
            other.m_value.reset();
        }

        push_coroutine * m_push;
        std::optional<value_type> m_value;
    };

    using function_type = std::function<void( pull_type& )>;
public:
    push_coroutine( const push_coroutine& ) = delete;
    push_coroutine& operator =( const push_coroutine& ) = delete;

    push_coroutine( const stack_t& stack, function_type&& function ) noexcept : m_context { &m_link, stack, {} }, m_pull( this ) {
        // Allocate space for function on stack
        auto * const functionOnStack = detail::stack_put( m_context.uc_stack, function );
        const auto callFunc = reinterpret_cast<void( * )( void )>( call );

        __agbabi_makecontext( &m_context, callFunc, 2, std::ref( m_pull ), functionOnStack );
        m_start = m_context.uc_mcontext;
    }

    push_coroutine( push_coroutine&& other ) noexcept : m_context { other.m_context }, m_link { other.m_link }, m_start { other.m_start }, m_pull( std::move( other.m_pull ) ) {
        other.m_context = {};
        other.m_link = {};
        other.m_start = {};
        m_pull.m_push = this;
        m_start.arm_r0 = reinterpret_cast<unsigned long int>( &m_pull ); // Update the initial m_pull address
        detail::stack_set_link( m_context.uc_stack, m_link );

        // Quirk: Moved coroutines are reset (only move coroutines that haven't been ran!)
        reset();
    }

    push_coroutine& operator ()( const value_type& value ) noexcept {
        if ( is_initialized() ) {
            __agbabi_swapcontext( &m_link, &m_context );
        }

        m_pull.m_value.emplace( value );
        __agbabi_swapcontext( &m_link, &m_context );
        return *this;
    }

    push_coroutine& operator ()( value_type&& value ) noexcept {
        if ( is_initialized() ) {
            __agbabi_swapcontext( &m_link, &m_context );
        }

        m_pull.m_value.emplace( std::move( value ) );
        __agbabi_swapcontext( &m_link, &m_context );
        return *this;
    }

    [[nodiscard]]
    explicit operator bool() const noexcept {
        return !m_pull.m_value.has_value();
    }
private:
    bool is_initialized() const noexcept {
        // Points to call method
        return m_context.uc_mcontext.arm_pc == m_start.arm_pc;
    }

    void reset() noexcept {
        m_context.uc_mcontext = m_start;
    }

    static void call( pull_type& pull, function_type * const function ) noexcept {
        ( *function )( pull );
        pull.m_push->reset();
    }

    ucontext_t m_context;
    ucontext_t m_link;
    mcontext_t m_start;
    pull_type m_pull;
};

} // agbabi
} // gba

#endif // __agb_abi
#endif // define GBAXX_EXT_AGBABI_PUSH_COROUTINE_HPP
