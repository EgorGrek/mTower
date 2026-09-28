#ifndef _STDIO_H_
#define _STDIO_H_

#include <stddef.h>
#include <stdarg.h>

typedef struct {
  int unused;
} FILE;

int printf(const char *fmt, ...);
int sprintf(char *str, const char *fmt, ...);
int snprintf(char *str, size_t size, const char *fmt, ...);
int vsnprintf(char *str, size_t size, const char *fmt, va_list ap);

#endif
