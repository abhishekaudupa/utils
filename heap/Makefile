all: debug release

debug:
	gcc -Wall -Wextra -Werror -O0 -g heap.c heaptest.c -o heaptest_d

release: 
	gcc -Wall -Wextra -Werror -DNDEBUG -O2 heap.c heaptest.c -o heaptest_r

clean:
	@rm -rf heaptest_r heaptest_d

.PHONY: clean debug release
