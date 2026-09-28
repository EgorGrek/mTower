/**
 * @file        arch/riscv32/esp32c3/src/esp-hal/libc_min.c
 * @brief       Minimal C library routines when host GCC lacks newlib
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t n)
{
  unsigned char *d = dest;
  const unsigned char *s = src;

  while (n--) {
    *d++ = *s++;
  }
  return dest;
}

void *memset(void *s, int c, size_t n)
{
  unsigned char *p = s;

  while (n--) {
    *p++ = (unsigned char)c;
  }
  return s;
}

void *memmove(void *dest, const void *src, size_t n)
{
  unsigned char *d = dest;
  const unsigned char *s = src;

  if (d < s) {
    while (n--) {
      *d++ = *s++;
    }
  } else {
    d += n;
    s += n;
    while (n--) {
      *--d = *--s;
    }
  }
  return dest;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
  const unsigned char *a = s1;
  const unsigned char *b = s2;

  while (n--) {
    if (*a != *b) {
      return (int)*a - (int)*b;
    }
    a++;
    b++;
  }
  return 0;
}

size_t strlen(const char *s)
{
  size_t n = 0;

  while (*s++) {
    n++;
  }
  return n;
}

char *strcpy(char *dest, const char *src)
{
  char *d = dest;

  while ((*d++ = *src++) != '\0') {
  }
  return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
  char *d = dest;

  while (n && (*d++ = *src++) != '\0') {
    n--;
  }
  while (n--) {
    *d++ = '\0';
  }
  return dest;
}

void abort(void)
{
  for (;;) {
  }
}
