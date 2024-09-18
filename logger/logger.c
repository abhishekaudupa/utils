#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "logger.h"

	void 
log_msg(const LOG_LEVEL level,
		const char *const filename,
		const char *const function_name,
		const int line_number,
		FILE *const logfile,
		const char *const fmt, 
		...) 
{
	assert(filename);
	assert(function_name);
	assert(fmt);
	assert(logfile);

	va_list args;
	char *filename_nodir = NULL;
	struct timeval tv;
	struct tm broken_time;

	va_start(args, fmt);

	//don't print the whole filepath.
	filename_nodir = strrchr(filename, '/');
	if(!filename_nodir)
		memcpy(filename_nodir, filename, sizeof(filename));
	else
		++filename_nodir;

	if(gettimeofday(&tv, NULL) == 0) {
		if(localtime_r(&(tv.tv_sec), &broken_time))
			fprintf(logfile, "%02d-%02d-%04d, %02d:%02d:%02d.%03ld, ",
					broken_time.tm_mday,
					broken_time.tm_mon + 1,
					broken_time.tm_year + 1900,
					broken_time.tm_hour,
					broken_time.tm_min,
					broken_time.tm_sec,
					tv.tv_usec / 1000);
	}

	fprintf(logfile, "%s, %s, %d, ", 
			filename_nodir, 
			function_name, 
			line_number);

	switch(level) {
		case INFO: 
			fprintf(logfile, "[INFO]: ");
			break;
		case WARNING:
			fprintf(logfile, "[WARNING]: ");
			break;
		case ERROR:
			fprintf(logfile, "[ERROR]: ");
			break;
		case DEBUG:
			fprintf(logfile, "[DEBUG]: ");
			break;
		default:
			assert(0);
	}

	vfprintf(logfile, fmt, args);
	fprintf(logfile, "\n");

	va_end(args);
}
