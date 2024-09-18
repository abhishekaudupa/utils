#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
	INFO,
	WARNING,
	ERROR,
	DEBUG
} LOG_LEVEL;

//#define NDEBUG

#define LOG_INFO(logfile, fmt, ...) 	log_msg(INFO, __FILE__, __func__, __LINE__, logfile, fmt, ##__VA_ARGS__)
#define LOG_WARNING(logfile, fmt, ...) 	log_msg(WARNING, __FILE__, __func__, __LINE__, logfile, fmt, ##__VA_ARGS__)
#define LOG_ERROR(logfile, fmt, ...) 	log_msg(ERROR, __FILE__, __func__, __LINE__, logfile, fmt, ##__VA_ARGS__)

#ifndef NDEBUG

#define LOG_DEBUG(logfile, fmt, ...) 	log_msg(DEBUG, __FILE__, __func__, __LINE__, logfile, fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG(logfile, fmt, ...)

#endif /* NDEBUG */

void 
log_msg(const LOG_LEVEL level,
		const char *const filename,
		const char *const function_name,
		const int line_number,
		FILE *const logfile,
		const char *const fmt, 
		...);

#endif /* LOGGER_H */
