#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include "heap.h"

#define ARR_SIZE(arr) 20

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

	printf("Insertion...\n");
	for(int i = 0; i < size; ++i) {
		insert_heap(heap, data + i);
	}

	pprev = NULL;
	printf("Deletion...\n");
	for(int i = 0; i < size; ++i) {
		delete_heap(heap, &deleted);
		if(!pprev) {
			pprev = &prev;
			prev = *(int*)deleted;
		} else {
			curr = *(int*)deleted;
			//assert((cbk(pprev, deleted) == true) || prev == curr);
			if(!(cbk(pprev, deleted) == true || prev == curr)) {
				printf("Test failed.\n");
				exit(EXIT_FAILURE);
			}
			prev = curr;
		}
	}
}

	int 
main()
{
	srand(time(NULL));
	int arr[HEAP_MAX_CAP];
	Heap *minheap, *maxheap;

	for(uint8_t i = 0; i < ARR_SIZE(arr); ++i) {
		arr[i] = rand() % 100;
	}

	minheap = init_heap(min_heap_cmp_clbk);
	maxheap = init_heap(max_heap_cmp_clbk);

	printf("Testing begin...\n");
	testHeap(minheap, arr, ARR_SIZE(arr), min_heap_cmp_clbk);
	testHeap(maxheap, arr, ARR_SIZE(arr), max_heap_cmp_clbk);

	finalize_heap(minheap, NULL);
	finalize_heap(maxheap, NULL);

	printf("All tests passed.\n");
}
