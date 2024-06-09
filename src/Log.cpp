#include "Phoenix/Log.hpp"
#include "cstdarg"
#include <cstdarg>
#include <cstdio>

void Log(const char* level, const char* filename, int line, const char* msg, ...) {
    va_list args;
    va_start(args, msg);
    printf("%s::%d - [%s]: ", filename, line, level);
    vprintf(msg, args);
    puts("");
    va_end(args);

}
