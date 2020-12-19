#ifndef GBAXX_EXT_AGBABI_COROUTINE_HPP
#define GBAXX_EXT_AGBABI_COROUTINE_HPP

#include <cstddef>
#include <tuple>

#if defined( __agb_abi )

#include <sys/ucontext.h>

extern "C" {

int __agbabi_getcontext( struct ucontext_t * ucp );
int __agbabi_setcontext( const ucontext_t * ucp) ;
void __agbabi_makecontext( struct ucontext_t * ucp, void ( * func )( void ), int argc, ... );
int __agbabi_swapcontext( struct ucontext_t * oucp, const ucontext_t * ucp );

}

#endif

namespace gba {
namespace agbabi {

template <typename R>
struct coroutine {
    class context {
    public:
        context( void * sp, std::size_t sz ) noexcept : m_link {}, m_context {}, m_returnContext {}, m_completed { false } {
            m_context.uc_stack.ss_sp = sp;
            m_context.uc_stack.ss_size = sz;
            m_context.uc_link = &m_returnContext;

            m_returnContext.uc_stack.ss_sp = sp;
            m_returnContext.uc_stack.ss_size = sz;
            m_returnContext.uc_link = &m_link;
        }

        template <class... Ts>
        void make( void( * fn )( void ), Ts... args ) {
            const auto fnptr = reinterpret_cast<void( * )( void )>( static_cast<void( * )( bool * )>( []( bool * complete ) {
                *complete = true;
            } ) );
            __agbabi_makecontext( &m_returnContext, fnptr, 1, &m_completed );

            __agbabi_makecontext( &m_context, fn, sizeof...( Ts ), args... );
        }

        void call() {
            __agbabi_swapcontext( &m_link, &m_context );
        }

        void yield() {
            __agbabi_swapcontext( &m_context, &m_link );
        }

        bool completed() const {
            return m_completed;
        }

    protected:
        ucontext_t m_link;
        ucontext_t m_context;
        ucontext_t m_returnContext;
        bool m_completed;
    };

    class pull_type;

    class push_type {
        friend pull_type;
    public:
        push_type( pull_type& pull ) noexcept : m_pull { pull }, m_value {} {}

        void operator ()( R value ) noexcept {
            m_value = value;
            m_pull.m_context->yield();
        }

    protected:
        pull_type& m_pull;
        volatile R m_value;
    };

    class pull_type {
        friend push_type;
    public:
        template <typename Fn, class... Ts>
        pull_type( void * sp, std::size_t sz, Fn&& fn, Ts... args ) noexcept : m_push( *this ), m_context { new context( sp, sz ) } {
            const auto fnptr = reinterpret_cast<void( * )( void )>( static_cast<void( * )( push_type&, Ts... )>( fn ) );
            m_context->make( fnptr, m_push, args... );

            m_context->call();
            if ( m_context->completed() ) {
                delete m_context;
                m_context = nullptr;
            }
        }

        ~pull_type() {
            if ( m_context ) {
                delete m_context;
            }
        }

        pull_type( const pull_type& ) = delete;
        pull_type& operator =( const pull_type& ) = delete;

        void operator ()( void ) noexcept {
            if ( m_context ) {
                m_context->call();
                if ( m_context->completed() ) {
                    delete m_context;
                    m_context = nullptr;
                }
            }
        }

        explicit operator bool() const noexcept {
            return m_context == nullptr || m_context->completed();
        }

        bool operator!() const noexcept {
            return m_context != nullptr && !m_context->completed();
        }

        R get() const noexcept {
            return m_push.m_value;
        }

        class iterator {
        public:
            iterator( pull_type& pull ) noexcept : m_pull { pull } {}
            iterator( pull_type& pull, int ) noexcept : m_pull { pull } {}

            bool operator !=( bool ) const noexcept {
                return !m_pull;
            }

            R operator *() noexcept {
                return m_pull.get();
            }

            iterator& operator ++() noexcept {
                m_pull();
                return *this;
            }

        protected:
            pull_type& m_pull;
        };

        iterator begin() noexcept {
            return iterator( *this );
        }

        bool end() noexcept {
            return false;
        }

    protected:
        push_type m_push;
        context * m_context;
    };
};

} // agbabi
} // gba

#endif // define GBAXX_EXT_AGBABI_COROUTINE_HPP
