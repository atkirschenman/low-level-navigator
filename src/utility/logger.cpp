#include "logger.h"
#include <pico/time.h>

        Logger::Logger(const char* cat): category(cat)
        {
        }

        void Logger::trace(const char *format, ...)
        {

            printf("1 %lu %s ", time_us_32()/1000, category);
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            va_end(args);

            printf("\n");
        }
        void Logger::info(const char *format, ...)
        {
            printf("2 %lu %s ", time_us_32()/1000, category);
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            va_end(args);
            printf("\n");
        }
        void Logger::warn(const char *format, ...)
        {
            printf("3 %lu %s ", time_us_32()/1000, category);
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            va_end(args);
            printf("\n");
        }
        void Logger::debug(const char *format, ...)
        {
            printf("4 %lu %s ", time_us_32()/1000, category);
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            va_end(args);
            printf("\n");
        }
        void Logger::error(const char *format, ...)
        {
            printf("5 %lu %s ", time_us_32()/1000, category);
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            va_end(args);
            printf("\n");
        }