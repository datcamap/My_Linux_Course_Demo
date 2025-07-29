#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

void initLogger(const char *filename, LogLevel_t level, LogMode_t mode)
{
    loggerConfig.logLevel = level,
    loggerConfig.logFileName = (NULL != filename) ? (char *)filename : "default.log";
    loggerConfig.ftoFile = mode;
}

void logMessage(LogLevel_t level, const char *file, const int line, const char *message, ...)
{
    if (level < LOG_EMERGENCY || level > LOG_DEBUG || level > loggerConfig.logLevel) {
        return; // Invalid log level
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

    if (loggerConfig.ftoFile == LOG_TO_CONSOLE_AND_FILE) {
        FILE *filep = fopen(loggerConfig.logFileName, "a");
        printf("I'm here");
        if (filep != NULL) {
            fprintf(filep, "%s%s", buffer1, buffer2);
            vfprintf(filep, message, args);
            fprintf(filep, "\n");
            fclose(filep);
        } else {
            fprintf(stderr, "Could not open log file: %s\n", loggerConfig.logFileName);
        }
    }

    va_end(args);
}

void setLogLevel(LogLevel_t level)
{
    if (level < LOG_EMERGENCY || level > LOG_DEBUG) {
        fprintf(stderr, "Invalid log level: %d\n", level);
        return; // Invalid log level
    }
    loggerConfig.logLevel = level;
}