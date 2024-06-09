#pragma once

#include <cstdlib>
#include <cstdio>

#define PHNX_ERR(msg, ...) do { Log("ERROR", __BASE_FILE__, __LINE__, msg, ## __VA_ARGS__);} while(false)
#define PHNX_FATAL(msg, ...) do { Log("FATAL", __BASE_FILE__, __LINE__, msg, ## __VA_ARGS__); exit(1); } while(false)

#ifndef _PHNX_DIST
#define PHNX_INFO(msg, ...) do {Log("INFO", __BASE_FILE__, __LINE__, msg, ## __VA_ARGS__);} while(false)
#else
#define PHNX_INFO(msg)
#endif

#ifndef NDEBUG
#define PHNX_DEBUG(msg, ...) do { Log("DEBUG", __BASE_FILE__, __LINE__, msg, ## __VA_ARGS__);} while(false)
#else
#define PHNX_DEBUG(msg, ...)
#endif

void Log(const char* level, const char* filename, int line, const char* msg, ...);
