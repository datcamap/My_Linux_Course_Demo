#include <stdio.h>
#include <stdarg.h>

typedef enum {
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
} LogLevel;

LogLevel CURRENT_LOG_LEVEL = LOG_LEVEL_DEBUG; // Mức log hiện tại

void log_message(LogLevel level, const char *format, ...) {
    if (level < CURRENT_LOG_LEVEL) return; // Bỏ qua nếu mức log thấp hơn cấu hình

    const char *level_strings[] = {
        "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
    };

    va_list args;
    va_start(args, format);
    fprintf(stderr, "[%s] ", level_strings[level]);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

int main() {
    log_message(LOG_LEVEL_DEBUG, "Đây là debug message");
    log_message(LOG_LEVEL_ERROR, "Có lỗi tại %s, dòng %d", __FILE__, __LINE__);
    return 0;
}
