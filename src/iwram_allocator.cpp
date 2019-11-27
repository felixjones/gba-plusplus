#include <gba/iwram_allocator.hpp>

#include <gba/tiny_alloc.hpp>

extern void * __iwram_overlay_end; // IWRAM "heap" start
extern void * __sp_usr; // User "stack" start

using namespace gba;

static auto heap_start = reinterpret_cast<uintptr>( &__iwram_overlay_end );
static auto heap_end = reinterpret_cast<uintptr>( &__sp_usr ) - 0x2000; // 8K stack

[[gnu::section( ".ewram" )]]
static util::tiny_alloc iwram_ta( heap_start, heap_end, 128, 16, 4 );

void * gba::iwram_malloc( std::size_t n ) {
	return iwram_ta.alloc( n );
}

void gba::iwram_free( void * p ) {
	iwram_ta.free( p );
}
