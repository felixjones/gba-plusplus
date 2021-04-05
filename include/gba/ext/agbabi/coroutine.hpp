#ifndef GBAXX_EXT_AGBABI_COROUTINE_HPP
#define GBAXX_EXT_AGBABI_COROUTINE_HPP

#if defined( __agb_abi )

#include <sys/ucontext.h>

extern "C" {

int __agbabi_getcontext( ucontext_t * );
int __agbabi_setcontext( const ucontext_t * ) ;
void __agbabi_makecontext( ucontext_t *, void ( * )( void ), int, ... );
int __agbabi_swapcontext( ucontext_t *, const ucontext_t * );

}

#include <cstddef>
#include <functional>

namespace gba {
namespace agbabi {

template <typename R>
struct coroutine {

    struct sentinel {};

    class pull_type;

    template <class PullType>
    class iterator {
        friend PullType;
    public:
        using value_type = typename PullType::value_type;
        using difference_type = std::ptrdiff_t;
        using reference_type = value_type&;
        using pointer_type = value_type *;

        iterator() = default;
        iterator( iterator& ) = default;
        iterator( iterator&& ) = default;
        iterator& operator =( iterator& ) = default;

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
        iterator( PullType& pull ) noexcept : m_pull { &pull } {
            ( *m_pull )();
        }

        PullType * m_pull;
    };

    class push_type {
        friend pull_type;
    public:
        void operator ()( R value ) noexcept {
            m_value = value;
            m_hasValue = true;
            __agbabi_swapcontext( &m_pull.m_context, &m_pull.m_link );
        }

    private:
        push_type( pull_type& pull ) noexcept : m_pull { pull }, m_hasValue { false }, m_value {} {}

        pull_type& m_pull;
        volatile bool m_hasValue;
        volatile R m_value;
    };

    class pull_type {
        friend class push_type;
    public:
        using value_type = R;

        template <typename Fn, class... Ts>
        pull_type( const stack_t& stack, Fn&& fn, Ts... args ) noexcept : m_context { &m_link, stack, {} },  m_push( *this ) {
            const auto fnPtr = reinterpret_cast<void( * )( void )>( static_cast<void( * )( push_type&, Ts... )>( fn ) );
            __agbabi_makecontext( &m_context, fnPtr, 1 + sizeof...( Ts ), std::ref( m_push ), std::forward<Ts>( args )... );
            m_start = m_context.uc_mcontext;
        }

        pull_type( const pull_type& ) = delete;
        pull_type& operator =( const pull_type& ) = delete;

        pull_type& operator ()( void ) noexcept {
            if ( !m_push.m_hasValue ) {
                m_context.uc_mcontext = m_start;
            } else {
                m_push.m_hasValue = false;
            }
            __agbabi_swapcontext( &m_link, &m_context );
            return *this;
        }

        [[nodiscard]]
        operator bool() const noexcept {
            return m_push.m_hasValue;
        }

        [[nodiscard]]
        R get() const noexcept {
            return m_push.m_value;
        }

        [[nodiscard]]
        iterator<pull_type> begin() noexcept {
            return iterator<pull_type>( *this );
        }

        [[nodiscard]]
        sentinel end() const noexcept {
            return {};
        }

    private:
        ucontext_t m_context;
        ucontext_t m_link;
        mcontext_t m_start;
        push_type m_push;
    };

};

template <>
struct coroutine<void> {

    struct sentinel {};

    class pull_type;

    class iterator {
        friend pull_type;
    public:
        [[nodiscard]]
        bool operator ==( sentinel ) const noexcept {
            return !m_pull;
        }

        [[nodiscard]]
        bool operator !=( sentinel ) const noexcept {
            return m_pull;
        }

        iterator& operator ++() noexcept {
            m_pull();
            return *this;
        }

        iterator& operator ++( int ) noexcept {
            m_pull();
            return *this;
        }

    private:
        iterator( pull_type& pull ) noexcept : m_pull { pull } {
            m_pull();
        }

        pull_type& m_pull;
    };

    class push_type {
        friend pull_type;
    public:
        void operator ()() noexcept {
            m_hasReturned = true;
            __agbabi_swapcontext( &m_pull.m_context, &m_pull.m_link );
        }

    private:
        push_type( pull_type& pull ) noexcept : m_pull { pull }, m_hasReturned { false } {}

        pull_type& m_pull;
        volatile bool m_hasReturned;
    };

    class pull_type {
        friend class push_type;
    public:
        template <typename Fn, class... Ts>
        pull_type( const stack_t& stack, Fn&& fn, Ts... args ) noexcept : m_context { &m_link, stack, {} },  m_push( *this ) {
            const auto fnPtr = reinterpret_cast<void( * )( void )>( static_cast<void( * )( push_type&, Ts... )>( fn ) );
            __agbabi_makecontext( &m_context, fnPtr, 1 + sizeof...( Ts ), std::ref( m_push ), std::forward<Ts>( args )... );
            m_start = m_context.uc_mcontext;
        }

        pull_type( const pull_type& ) = delete;
        pull_type& operator =( const pull_type& ) = delete;

        pull_type& operator ()( void ) noexcept {
            if ( !m_push.m_hasReturned ) {
                m_context.uc_mcontext = m_start;
            } else {
                m_push.m_hasReturned = false;
            }
            __agbabi_swapcontext( &m_link, &m_context );
            return *this;
        }

        [[nodiscard]]
        operator bool() const noexcept {
            return m_push.m_hasReturned;
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
        ucontext_t m_context;
        ucontext_t m_link;
        mcontext_t m_start;
        push_type m_push;
    };

};

} // agbabi
} // gba

#endif // __agb_abi

#endif // define GBAXX_EXT_AGBABI_COROUTINE_HPP
