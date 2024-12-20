#pragma once
#include <stdio.h>
#include <stdarg.h>
#include "pico/stdlib.h"

class Logger
{
    public:
        Logger(const char* cat);
        void trace(const char *format, ...);
        void info(const char *format, ...);
        void warn(const char *format, ...);
        void debug(const char *format, ...);
        void error(const char *format, ...);

    private:
        const char* category;
};