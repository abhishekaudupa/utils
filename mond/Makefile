CC = gcc
CFLAGS_RELEASE = -Wall -Werror -Wextra -O2
CFLAGS_DEBUG = -Wall -Werror -Wextra -O0 -g

SRC = mond.c

all: debug release

debug:
	$(CC) $(CFLAGS_DEBUG) mond.c -o mond_dbg

release:
	$(CC) $(CFLAGS_RELEASE) mond.c -o mond_rel

clean:
	@rm -rf mond_*; clear

.PHONY: clean debug release
