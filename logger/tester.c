#include <stdio.h>
#include "logger.h"

void somefunc() {
	LOG_INFO(stdout, "This is an info message 2.");
	LOG_WARNING(stdout, "This is a warning message 2.");
	LOG_ERROR(stdout, "This is an error message 2.");
	LOG_DEBUG(stdout, "This is a debug message 2.");
}

int main(int argc, char **argv) {
	LOG_INFO(stdout, "This is an info message.");
	LOG_WARNING(stdout, "This is a warning message.");
	LOG_ERROR(stdout, "This is an error message.");
	LOG_DEBUG(stdout, "This is a debug message.");
	printf("\n");
	somefunc();
}

