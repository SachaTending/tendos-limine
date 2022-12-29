#ifndef _TTY_H
#define _TTY_H

#include <limine_interface.h>
#include <stddef.h>

void vsprintf(char * str, void (*putchar)(const char *), const char * format, va_list arg);

void printf(const char * s, ...);

#endif