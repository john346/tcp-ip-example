#ifndef UTILS_H_
#define UTILS_H_

/* System headers */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>

int run_cmd(const char * format, ... );
uint16_t checksum(void *addr, int count);
void print_hexdump(char *str, int len);

#endif