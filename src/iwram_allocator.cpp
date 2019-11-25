#include <gba/iwram_allocator.hpp>

extern void * __iwram_overlay_end; // IWRAM "heap" start
extern void * __sp_usr; // User "stack" start

using namespace gba;

static auto heap_start = reinterpret_cast<uint8 *>( &__iwram_overlay_end );
static auto heap_end = reinterpret_cast<uint8 *>( &__sp_usr ) - 0x2000; // 8K stack

struct block {
	uint16	next;
	uint16	size;
};

static block * first_free = reinterpret_cast<block *>( heap_start );

[[gnu::constructor]]
static void iwram_allocator_init() {
	first_free->next = 0;
	first_free->size = 0;
}

void * gba::iwram_malloc( std::size_t n ) {
	return nullptr;
}

void gba::iwram_free( void * p ) {

}
