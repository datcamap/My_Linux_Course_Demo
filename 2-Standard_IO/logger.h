#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>

#define LOG_MESSAGE(level, ...)    logMessage(level, __FILE__, __LINE__, __VA_ARGS__)

typedef enum {
    LOG_EMERGENCY,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} LogLevel_t;

typedef enum {
    LOG_TO_CONSOLE,
    LOG_TO_CONSOLE_AND_FILE,
} LogMode_t;

typedef struct LoggerConfig {
    LogLevel_t logLevel;
    char *logFileName;
    uint8_t ftoFile;
} LoggerConfig_t;

static LoggerConfig_t loggerConfig = {
    .logLevel = LOG_INFO,
    .logFileName = "default.log",
    .ftoFile = LOG_TO_CONSOLE
};

static const char *logLevelStrings[] = {
    "EMERGENCY",
    "ALERT",
    "CRITICAL",
    "ERROR",
    "WARNING",
    "NOTICE",
    "INFO",
    "DEBUG"
};

void initLogger(const char *filename, LogLevel_t level, LogMode_t mode);
void logMessage(LogLevel_t level, const char *file, const int line, const char *message, ...);
void setLogLevel(LogLevel_t level);

#endif // LOGGER_H