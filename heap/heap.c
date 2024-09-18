#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include "heap.h"

#define ARR_SIZE(arr)					(sizeof(arr)/sizeof(arr[0]))
#define HEAP_CLBK(heap_ptr, i, j)		(heap_ptr->comparison_callback)(*get_data(heap, i), *get_data(heap, j))

typedef struct {
	void *data;
} Heap_Node;

typedef struct Heap {
	Heap_Node static_heap_arr[HEAP_MAX_CAP];
	Heap_Node *heap_arr;
	heap_index_t size;
	heap_index_t max_size_reached;
	heap_index_t capacity;
	bool (*comparison_callback)(const void *const parent, const void *const child);
} Heap;

	static void
**get_data(const Heap *const heap,
		const heap_index_t index)
{
	assert(heap);
	assert(index < heap->max_size_reached);
	return &(heap->heap_arr)[index].data;
}

	static void
set_data(Heap *const heap,
		const heap_index_t index,
		void *const data)
{
	assert(heap);
	assert(index < heap->capacity);
	assert(data);
	(heap->heap_arr)[index].data = data;
}

	static void
swap_data(Heap *const heap,
		const heap_index_t i,
		const heap_index_t j)
{
	assert(heap);
	assert(i < heap->size);
	assert(j < heap->size);

	void *temp = *get_data(heap, i);
	*get_data(heap, i) = *get_data(heap, j);
	*get_data(heap, j) = temp;
}

	static void 
access_heap(const Heap *const heap,
		void (*callback)(const void *const),
		const heap_index_t max_index)
{
	assert(max_index < heap->max_size_reached);
	assert(callback);

	for(heap_index_t i = 0; i <= max_index; ++i) {
		callback(*get_data(heap, i));
	}
}

	Heap
*init_heap(bool (*comparison_callback_supplied)(const void *const, const void *const))
{
	if(comparison_callback_supplied == NULL)
		return NULL;

	Heap *heap = malloc(sizeof(*heap));
	if(heap == NULL)
		return NULL;

	heap->heap_arr = heap->static_heap_arr;
	heap->capacity = HEAP_MAX_CAP;
	heap->size = 0;
	heap->max_size_reached = 0;
	heap->comparison_callback = comparison_callback_supplied;

	return heap;
}

	STATUS
insert_heap(Heap *const heap,
		void *const data)
{
	heap_index_t bubble_index, parent_index;

	if(heap == NULL)
		return ERR_NULL_INPUT;

	if(data == NULL)
		return ERR_NULL_INPUT;

	if(heap->size >= heap->capacity)
		return ERR_CAP_LIMIT;

	if(heap->size == 0) {
		set_data(heap, 0, data);
		heap->size = 1;
		if(heap->size > heap->max_size_reached)
			heap->max_size_reached = heap->size;
		return SUCCESS;
	}

	bubble_index = heap->size;
	set_data(heap, bubble_index, data);

	++(heap->size);
	if(heap->size > heap->max_size_reached)
		heap->max_size_reached = heap->size;

	while(1) {
		parent_index = (bubble_index - 1) / 2;

		if(HEAP_CLBK(heap, parent_index, bubble_index) == true)
			break;

		swap_data(heap, parent_index, bubble_index);

		bubble_index = parent_index;
		if(bubble_index == 0)
			break;
	}

	return SUCCESS;
}

	STATUS
delete_heap(Heap *const heap,
		void **deleted_data)
{
	heap_index_t lc_index, rc_index, curr_index, swap_index;

	if(heap == NULL)
		return ERR_NULL_INPUT;

	if(heap->size == 0)
		return SUCCESS;

	if(deleted_data != NULL)
		*deleted_data = *get_data(heap, 0);

	swap_data(heap, 0, heap->size - 1);
	--(heap->size);

	curr_index = 0;
	while(1) {
		lc_index = 2 * curr_index + 1;
		rc_index = 2 * curr_index + 2;

		if(lc_index >= heap->size 
				&& rc_index >= heap->size)
			break;

		if(lc_index >= heap->size)
			swap_index = rc_index;
		else if(rc_index >= heap->size)
			swap_index = lc_index;
		else if(HEAP_CLBK(heap, lc_index, rc_index) == true)
			swap_index = lc_index;
		else
			swap_index = rc_index;

		if(HEAP_CLBK(heap, curr_index, swap_index) == true)
			break;

		swap_data(heap, curr_index, swap_index);

		curr_index = swap_index;
	}

	return SUCCESS;
}

	void
finalize_heap(Heap *const heap,
		void (*free_callback)(void*))
{
	if(free_callback != NULL)
		for(heap_index_t i = 0; i < heap->max_size_reached; ++i)
			free_callback(*get_data(heap, i));
	free(heap);
}

#ifndef NDEBUG

	void
print_heap(const Heap *const heap,
		void (*print_data)(const void *const))
{
	if(!heap || !print_data)
		return;

	access_heap(heap, print_data, heap->size - 1);
}

	void
debug_print_heap(const Heap *const heap,
		void (*print_data)(const void *const))
{
	if(!heap || !print_data)
		return;

	access_heap(heap, print_data, heap->max_size_reached - 1);
}

#endif /* NDEBUG */
