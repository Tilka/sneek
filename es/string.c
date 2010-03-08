/*
 *  linux/lib/string.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#include "string.h"

size_t strnlen(const char *s, size_t count)
{
	const char *sc;

	for (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

size_t strlen(const char *s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

char *strncpy(char *dst, const char *src, size_t n)
{
	char *ret = dst;

	while (n && (*dst++ = *src++))
		n--;

	while (n--)
		*dst++ = 0;

	return ret;
}
int _sprintf( char *buf, const char *fmt, ... )
{
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsprintf(buf, fmt, args);
	va_end(args);

	return i;
}

size_t strlcpy(char *dest, const char *src, size_t maxlen)
{
	size_t len,needed;

	len = needed = strnlen(src, maxlen-1) + 1;
	if (len >= maxlen)
		len = maxlen-1;

	memcpy8(dest, src, len);
	dest[len]='\0';

	return needed-1;
}

char *strcpy(char *dst, const char *src)
{
	char *ret = dst;

	while ((*dst++ = *src++))
		;

	return ret;
}

int strcmp(const char *p, const char *q)
{
	for (;;) {
		unsigned char a, b;
		a = *p++;
		b = *q++;
		if (a == 0 || a != b)
			return a - b;
	}
}

int strncmp(const char *p, const char *q, size_t n)
{
	while (n-- != 0) {
		unsigned char a, b;
		a = *p++;
		b = *q++;
		if (a == 0 || a != b)
			return a - b;
	}
	return 0;
}
void *memcpy16(void *dst, const void *src, size_t n)
{
	unsigned short *p;
	const unsigned short *q;

	for (p = dst, q = src; n; n-=2)
		*p++ = *q++;

	return dst;
}
void *memcpy32(void *dst, const void *src, size_t n)
{
	unsigned int *p;
	const unsigned int *q;

	for (p = dst, q = src; n; n-=4)
		*p++ = *q++;

	return dst;
}
void *memset32(void *dst, int x, size_t n)
{
	unsigned int *p;

	for (p = dst; n; n-=4)
		*p++ = x;

	return dst;
}
void *memset8(void *dst, int x, size_t n)
{
	unsigned char *p;

	for (p = dst; n; n-=4)
		*p++ = x;

	return dst;
}

void *memcpy8(void *dst, const void *src, size_t n)
{
	unsigned char *p;
	const unsigned char *q;

	for (p = dst, q = src; n; n--)
		*p++ = *q++;

	return dst;
}


int memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *us1 = (unsigned char *) s1;
	unsigned char *us2 = (unsigned char *) s2;
	while (n-- != 0) {
		if (*us1 != *us2)
			return (*us1 < *us2) ? -1 : +1;
		us1++;
		us2++;
	}
	return 0;
}

char *strchr(const char *s, int c)
{
	do {
		if(*s == c)
			return (char *)s;
	} while(*s++ != 0);
	return NULL;
}
#ifdef DEBUG
static char ascii(char s) {
  if(s < 0x20) return '.';
  if(s > 0x7E) return '.';
  return s;
}

void hexdump(void *d, int len)
{
  u8 *data;
  int i, off;
  data = (u8*)d;
  for (off=0; off<len; off += 16)
  {
    dbgprintf("%08x  ",off);
    for(i=0; i<16; i++)
      if((i+off)>=len)
		  dbgprintf("   ");
      else
		  dbgprintf("%02x ",data[off+i]);

    dbgprintf(" ");
    for(i=0; i<16; i++)
      if((i+off)>=len) dbgprintf(" ");
      else dbgprintf("%c",ascii(data[off+i]));
    dbgprintf("\n");
  }
}
#endif