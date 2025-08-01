#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

static LoggerConfig_t logger_config = {
    .logLevel = LOG_INFO,
    .logFileName = "default.log",
    .ftoFile = LOG_TO_CONSOLE
};

LoggerConfig_t *get_logger_config(void) {
    return &logger_config;
}

void init_logger(const char *file_name, LogLevel_t level, LogMode_t mode)
{
    logger_config.logLevel = level,
    logger_config.logFileName = (NULL != file_name) ? (char *)file_name : "default.log";
    logger_config.ftoFile = mode;
}

void log_message(LogLevel_t level, const char *file, const int line, const char *message, ...)
{
    if (level < LOG_EMERGENCY || level > LOG_DEBUG || level > logger_config.logLevel) {
        return;
    }

    va_list args;
    va_start(args, message);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char buffer1[64];
    strftime(buffer1, sizeof(buffer1), "[%Y-%m-%d %H:%M:%S]", t);
    char buffer2[64];
    snprintf(buffer2, sizeof(buffer2), "[%s][%s:%d] - ", logLevelStrings[level], file, line);
    
    printf("%s%s", buffer1, buffer2);
    vprintf(message, args);
    printf("\n");

    if (logger_config.ftoFile == LOG_TO_CONSOLE_AND_FILE) {
        FILE *filep = fopen(logger_config.logFileName, "a");
        //printf("I'm here");
        if (filep != NULL) {
            fprintf(filep, "%s%s", buffer1, buffer2);
            vfprintf(filep, message, args);
            fprintf(filep, "\n");
            fclose(filep);
        } else {
            fprintf(stderr, "Could not open log file: %s\n", logger_config.logFileName);
        }
    }

    va_end(args);
}

void set_logLevel(LogLevel_t level)
{
    if (level < LOG_EMERGENCY || level > LOG_DEBUG) {
        fprintf(stderr, "Invalid log level: %d\n", level);
        return;
    }
    logger_config.logLevel = level;
}