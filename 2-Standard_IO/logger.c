#include "logger.h"

static logger_config_t logger_config = {
    .log_level = LOG_INFO,
    .log_file_name = "default.log",
    .f_to_file = LOG_TO_CONSOLE
};

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

logger_config_t *get_logger_config(void) {
    return &logger_config;
}

void init_logger(const char *file_name, log_level_t level, LogMode_t mode)
{
    logger_config.log_level = level,
    logger_config.log_file_name = (NULL != file_name) ? (char *)file_name : "default.log";
    logger_config.f_to_file = mode;
}

void log_message(log_level_t level, const char *file, const int line, const char *message, ...)
{
    if (level < LOG_EMERGENCY || level > LOG_DEBUG || level > logger_config.log_level) {
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
    printf("%s%s", buffer1, buffer2);
    vprintf(message, args);
    printf("\n");

    // Write to file
    if (logger_config.f_to_file == LOG_TO_CONSOLE_AND_FILE) {
        FILE *filep = fopen(logger_config.log_file_name, "a");
        //printf("I'm here");
        if (filep != NULL) {
            fprintf(filep, "%s%s", buffer1, buffer2);
            vfprintf(filep, message, args2);
            fprintf(filep, "\n");
            fclose(filep);
        } else {
            fprintf(stderr, "Could not open log file: %s\n", logger_config.log_file_name);
        }
    }

    va_end(args);
}

void set_log_level(log_level_t level)
{
    if (level < LOG_EMERGENCY || level > LOG_DEBUG) {
        fprintf(stderr, "Invalid log level: %d\n", level);
        return;
    }
    logger_config.log_level = level;

    LOG_MESSAGE(logger_config.log_level,"Log level changed to %s", log_level_strings[logger_config.log_level]);
}