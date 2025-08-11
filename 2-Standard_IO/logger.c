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

void log_message(log_level_t level, const char *file, const int line, const char *message, ...)
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

void init_logger(log_level_t log_level, const char* log_file_name, log_mode_t log_mode)
{
    logger.config.level = log_level;
    snprintf(logger.config.file_name, sizeof(logger.config.file_name), "%s", log_file_name);
    logger.config.mode = log_mode;
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
