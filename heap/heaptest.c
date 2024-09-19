#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include "heap.h"

	void
print_int(const void *const integer)
{
	printf("%d ", *(int*)integer);
}

	bool
max_heap_cmp_clbk(const void *const parent, const void *const child)
{
	return ((*(int*)parent) > (*(int*)child))? true: false;
}

	bool
min_heap_cmp_clbk(const void *const parent, const void *const child)
{
	return ((*(int*)parent) < (*(int*)child))? true: false;
}

void testHeap(Heap *heap, 
		int *data, 
		int size, 
		bool (*cbk)(const void *const, const void *const)) {
	int prev, curr, *pprev;
	void *deleted = NULL;

	for(int i = 0; i < size; ++i) {
		insert_heap(heap, data + i);
	}

	pprev = NULL;
	for(int i = 0; i < size; ++i) {
		delete_heap(heap, &deleted);
		if(!pprev) {
			pprev = &prev;
			prev = *(int*)deleted;
		} else {
			curr = *(int*)deleted;
			if(!(cbk(pprev, deleted) == true || prev == curr)) {
				printf("Test failed.\n");
				exit(EXIT_FAILURE);
			}
			prev = curr;
		}
	}
}

void testHeap2(Heap *heap)
{
	for(int i = 0; i < HEAP_MAX_CAP; ++i) {
		int *data = malloc(sizeof(*data));
		*data = rand() %  100;
		insert_heap(heap, data);
	}
	
	for(int i = 0; i < HEAP_MAX_CAP; ++i) {
		delete_heap(heap, NULL);
	}
}

	int 
main()
{
	srand(time(NULL));
	int arr[HEAP_MAX_CAP];
	Heap *minheap, *maxheap, *dynheap;

	for(uint8_t i = 0; i < HEAP_MAX_CAP; ++i) {
		arr[i] = rand() % 100;
	}

	minheap = init_heap(min_heap_cmp_clbk);
	maxheap = init_heap(max_heap_cmp_clbk);
	dynheap = init_heap(min_heap_cmp_clbk);

	testHeap(minheap, arr, HEAP_MAX_CAP, min_heap_cmp_clbk);
	testHeap(maxheap, arr, HEAP_MAX_CAP, max_heap_cmp_clbk);
	testHeap2(dynheap);

	finalize_heap(minheap, NULL);
	finalize_heap(maxheap, NULL);
	finalize_heap(dynheap, free);

	printf("All tests passed.\n");
}
