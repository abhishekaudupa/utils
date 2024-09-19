all: debug release test 

debug:
	gcc -Wall -Wextra -Werror -O0 -g heap.c heaptest.c -o heaptest_d

release: 
	gcc -Wall -Wextra -Werror -DNDEBUG -O2 heap.c heaptest.c -o heaptest_r

test:
	@./heaptest_r
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./heaptest_r
	@./heaptest_d
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./heaptest_d

clean:
	@rm -rf heaptest_r heaptest_d

.PHONY: all clean debug release test
