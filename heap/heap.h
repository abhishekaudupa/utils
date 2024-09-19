#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <stdbool.h>

#ifndef HEAP_MAX_CAP
#define HEAP_MAX_CAP 20
#endif /* HEAP_MAX_CAP */

typedef struct Heap Heap;

typedef enum {
	SUCCESS,
	FAILURE,
	ERR_NULL_INPUT,
	ERR_CAP_LIMIT,
	ERR_NO_MEM
} STATUS;

#ifndef NDEBUG

void
access_normal_heap(const Heap *const heap,
		void (*print_data)(const void *const));

void
access_extended_heap(const Heap *const heap,
		void (*print_data)(const void *const));

#endif /* NDEBUG */

Heap
*init_heap(bool (*comparison_callback_supplied)(const void *const, const void *const));

STATUS
insert_heap(Heap *const heap,
		void *const data);

STATUS
delete_heap(Heap *const heap,
		void **deleted_data);

void
finalize_heap(Heap *const heap,
		void (*free_callback)(void*));

#endif /* HEAP_H */
