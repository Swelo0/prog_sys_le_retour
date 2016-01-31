#ifndef _ULIBC_H_
#define _ULIBC_H_

#include "../common/types.h"
#include "../common/syscall_nb.h"
#include "../common/pfs_common.h"

extern int syscall(uint32_t nb, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t tss_selector);	

int read_file(char *filename, uchar *buf);
int get_stat(char *filename, stat_t *stat);
int remove_file(char *filename);
file_iterator_t* get_file_iterator();
int get_next_file(char *filename, file_iterator_t *it);

int exec(char *filename);
void exit();

int strlen(char *s);
int atoi(char *s);

int getc();
void putc(char c);
void puts(char *str);
void printf(char *fmt, ...);

void sleep(uint ms);
uint get_ticks();

char * strtok(register char *, register const char *);
int strncmp(const char *p, const char *q, uint n);

#endif