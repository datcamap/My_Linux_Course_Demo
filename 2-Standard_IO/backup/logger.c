#include "logger.h"

static logger_t logger;

static const char *log_level_strings[] = {
    "EMERGENCY",
    "ALERT",
    "CRITICAL",
    "ERROR",
    "WARNING",
    "NOTICE",
    "INFO",
    "DEBUG"
};

static void log_message(log_level_t level, const char *file, const int line, const char *message, ...)
{
    if (level < LOG_EMERGENCY || level > LOG_DEBUG || level > logger.config.level) {
        return;
    }

    va_list args;
    va_list args2;
    va_start(args, message);
    va_copy(args2, args);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char buffer1[64];
    strftime(buffer1, sizeof(buffer1), "[%Y-%m-%d %H:%M:%S]", t);
    char buffer2[64];
    snprintf(buffer2, sizeof(buffer2), "[%s][%s:%d] - ", log_level_strings[level], file, line);
    
    // Print to stdout
    if ( logger.config.mode == LOG_TO_CONSOLE_AND_FILE
        || logger.config.mode == LOG_TO_CONSOLE ) {
        printf("%s%s", buffer1, buffer2);
        vprintf(message, args);
        printf("\n");
    }

    // Write to file
    if ( logger.config.mode == LOG_TO_CONSOLE_AND_FILE
        || logger.config.mode == LOG_TO_FILE ) {
        FILE *filep = fopen(logger.config.file_name, "a");
        //printf("I'm here");
        if (filep != NULL) {
            fprintf(filep, "%s%s", buffer1, buffer2);
            vfprintf(filep, message, args2);
            fprintf(filep, "\n");
            fclose(filep);
        } else {
            fprintf(stderr, "Could not open log file: %s\n", logger.config.file_name);
        }
    }

    va_end(args);
}

#define EMERGENCY_LOG(message, ...)      log_message(LOG_EMERGENCY, __FILE__, __LINE__, __VA_ARGS__)
#define AlERT_LOG(message, ...)          log_message(LOG_ALERT, __FILE__, __LINE__, __VA_ARGS__)
#define CRITICAL_LOG(message, ...)       log_message(LOG_CRITICAL, __FILE__, __LINE__, __VA_ARGS__)
#define ERROR_LOG(message, ...)          log_message(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define WARNING_LOG(message, ...)        log_message(LOG_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define NOTICE_LOG(message, ...)         log_message(LOG_NOTICE, __FILE__, __LINE__, __VA_ARGS__)
#define INFO_LOG(message, ...)           log_message(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define DEBUG_LOG(message, ...)          log_message(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)

// static void log_emergency(const char *message, ...) {
//     va_list args;
//     va_start(args, message);
//     LOG_MESSAGE(LOG_EMERGENCY, message, args);
// }

// static void log_alert(const char *message, ...) {
//     va_list args;
//     va_start(args, message);
//     LOG_MESSAGE(LOG_ALERT, message, args);
// }

// static void log_critical(const char *message, ...) {
//     va_list args;
//     va_start(args, message);
//     LOG_MESSAGE(LOG_CRITICAL, message, args);
// }

// static void log_error(const char *message, ...) {
//     va_list args;
//     va_start(args, message);
//     LOG_MESSAGE(LOG_ERROR, message, args);
// }

// static void log_warning(const char *message, ...) {
//     va_list args;
//     va_start(args, message);
//     LOG_MESSAGE(LOG_WARNING, message, args);
// }

// static void log_notice(const char *message, ...) {
//     va_list args;
//     va_start(args, message);
//     LOG_MESSAGE(LOG_NOTICE, message, args);
// }

// static void log_info(const char *message, ...) {
//     va_list args;
//     va_start(args, message);
//     LOG_MESSAGE(LOG_INFO, message, args);
// }

// static void log_debug(const char *message, ...) {
//     va_list args;
//     va_start(args, message);
//     LOG_MESSAGE(LOG_DEBUG, message, args);
// }

logger_t init_logger(log_level_t log_level, const char* log_file_name, log_mode_t log_mode)
{
    logger.config.level = log_level;
    snprintf(logger.config.file_name, sizeof(logger.config.file_name), "%s", log_file_name);
    logger.config.mode = log_mode;

    logger.e = EMERGENCY_LOG;
    logger.a = AlERT_LOG;
    logger.c = CRITICAL_LOG;
    logger.err = ERROR_LOG;
    logger.w = WARNING_LOG;
    logger.n = NOTICE_LOG;
    logger.i = INFO_LOG;
    logger.d = DEBUG_LOG;

    return logger;
}

void set_log_level(log_level_t log_level)
{
    if (log_level < LOG_EMERGENCY || log_level > LOG_DEBUG) {
        fprintf(stderr, "Invalid log level: %d\n", log_level);
        return;
    }
    logger.config.level = log_level;

    LOG_MESSAGE(logger.config.level,"Log level changed to %s", log_level_strings[logger.config.level]);
}
