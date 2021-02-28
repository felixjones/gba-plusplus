#ifndef GBAXX_EXT_AGBABI_COROUTINE_HPP
#define GBAXX_EXT_AGBABI_COROUTINE_HPP

#include <cstddef>
#include <functional>

#if defined( __agb_abi )

#include <sys/ucontext.h>

extern "C" {

int __agbabi_getcontext( struct ucontext_t * );
int __agbabi_setcontext( const ucontext_t * ) ;
void __agbabi_makecontext( struct ucontext_t *, void ( * )( void ), int, ... );
int __agbabi_swapcontext( struct ucontext_t *, const ucontext_t * );

}

#endif

namespace gba {
namespace agbabi {
    
template <typename R>
struct coroutine {

    class pull_type;

    class push_type {
        friend pull_type;
    protected:
        push_type( pull_type& pull ) noexcept : m_value {}, m_pull { pull } {}
    public:
        void operator ()( R value ) noexcept {
            m_value = value;
            m_pull.join();
        }

        explicit operator bool() const noexcept {
            return m_pull;
        }

        bool operator!() const noexcept {
            return !m_pull;
        }

    protected:
        volatile R m_value;
    private:
        pull_type& m_pull;
    };

    class pull_type {
        friend push_type;
    public:
        template <typename Fn, class... Ts>
        pull_type( void * sp, std::size_t sz, Fn&& fn, Ts... args ) noexcept : 
            m_push( *this ), m_startContext {}, m_link {}, m_fiber {}
        {
            m_fiber.uc_link = &m_link;
            m_fiber.uc_stack.ss_sp = sp;
            m_fiber.uc_stack.ss_size = sz;
            
            const auto fnPtr = reinterpret_cast<void( * )( void )>( static_cast<void( * )( push_type&, Ts... )>( fn ) );

            __agbabi_makecontext( &m_fiber, fnPtr, 2 + sizeof...( Ts ),
                std::ref( m_push ),
                std::forward<Ts>( args )...
            );
            m_startContext = m_fiber.uc_mcontext;

            __agbabi_swapcontext( &m_link, &m_fiber );
        }

        pull_type( const pull_type& ) = delete;
        pull_type& operator =( const pull_type& ) = delete;

        void operator ()( void ) noexcept {
            if ( m_link.uc_stack.ss_size == 0 ) {
                // Restartable co-routine
                m_fiber.uc_mcontext = m_startContext;
            } else {
                m_link.uc_stack.ss_size = 0; // HACK : Reset yield flag
            }
            __agbabi_swapcontext( &m_link, &m_fiber );
        }

        explicit operator bool() const noexcept {
            return m_link.uc_stack.ss_size == 0;
        }

        bool operator!() const noexcept {
            return m_link.uc_stack.ss_size != 0;
        }

        R get() const noexcept {
            return m_push.m_value;
        }

        /**
         * 
         */ 
        class iterator {
        public:
            iterator( pull_type& pull ) noexcept : m_pull { pull } {}

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
        void join() noexcept {
            m_link.uc_stack.ss_size = 1; // HACK : Set yield flag
            __agbabi_swapcontext( &m_fiber, &m_link );
        }

        push_type m_push;
        mcontext_t m_startContext;
        ucontext_t m_link;
        ucontext_t m_fiber;
    };

};

} // agbabi
} // gba

#endif // define GBAXX_EXT_AGBABI_COROUTINE_HPP
