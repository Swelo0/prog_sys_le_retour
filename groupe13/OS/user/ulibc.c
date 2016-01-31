#include "ulibc.h"

int read_file(char* filename, uchar* buf) { 
	return syscall(SYSCALL_FILE_READ, (uint32_t) filename, (uint32_t) buf, 0, 0, 0);
}

int get_stat(char* filename, stat_t* stat) { 
	return syscall(SYSCALL_FILE_STAT, (uint32_t) filename, (uint32_t) stat, 0, 0, 0);
}

int remove_file(char* filename) { 
	return syscall(SYSCALL_FILE_REMOVE, (uint32_t) filename, 0, 0, 0, 0);
}

file_iterator_t* get_file_iterator() {  
	file_iterator_t* it;
	syscall(SYSCALL_FILE_ITERATOR, (uint32_t) it, 0, 0, 0, 0);
	return (file_iterator_t*) it;
}

int get_next_file(char* filename, file_iterator_t* it) { 
	return syscall(SYSCALL_FILE_NEXT, (uint32_t) filename, (uint32_t) it, 0, 0, 0);
}

int exec(char* filename) { 
	return syscall(SYSCALL_EXEC, (uint32_t) filename, 0, 0, 0, 0);
}

void exit() { 
	// Code was here.
}

int strlen(char* s) { 
	int l = 0;
	while (s++) l++;
	return l++;
}

int atoi(char* s) { 
	int k = 0;
    while (*s) {
        s = (char*) (k << 3) + (k << 1) + (*s) - '0';
        s++;
    }
    return k;
}

int getc() { 
	return syscall(SYSCALL_GETC, 0, 0, 0, 0, 0);
}

void putc(char c) {
	syscall(SYSCALL_PUTC, (uint32_t) c, 0, 0, 0, 0);
}

void puts(char* str) { 
	syscall(SYSCALL_PUTS, (uint32_t) str, 0, 0, 0, 0);
}

void print_int(int32_t n)
{
    if (n < 0)
    {
        putc('-');
        print_int(-n);
    }
    else
    {
        int upperRank = n / 10;
        if (upperRank)
        {
            print_int(upperRank);
        }
        putc((char)(n % 10 + 48));
    }
}

void print_hex(uint32_t n)
{
    int upperRank = n / 16;
    int unit = n % 16;
    
    if (upperRank)
    {
        print_hex(upperRank);
    }
    else
    {
        puts("0x");
    }
    
    // Prints the right character (digit or letter)
    if (unit >= 0 && unit <= 9)
    {
        putc((char)(unit + 48));
    }
    else
    {
        putc((char)(unit + 55));
    }
}

void printf(char* frmt, ...) { 

	// Pointer to the current argument
    uint32_t *args = (uint32_t*)(&frmt) + 1;
    
    // Prints the format string
    while (*frmt != '\0')
    {
        // If a format code is found
        if (*frmt == '%')
        {
            frmt++;
            switch (*frmt)
            {
            case '%': // Escapes the % character
                putc('%');
                break;
            
            case 'c': // Inserts a character
                putc(*((char*)args));
                args++;
                break;
                
            case 's': // Inserts a string
                puts(*((char**)args));
                args++;
                break;
                
            case 'd': // Inserts a signed integer
                print_int(*((int*)args));
                args++;
                break;
                
            case 'x': // Inserts an unsigned hexadecimal integer
                print_hex(*((int*)args));
                args++;
                break;
                
            default:
                break;
            }
        }
        else
        {
            putc(*frmt);
        }
        frmt++;
    }
}

void sleep(uint ms) { 

	/* Ticks à attendre
	uint wait = (1193180 / frequence_divise) * (ms / 1000);
	// Référence
	uint ref = ticks;
	// Boucle
	while (get_ticks() <= (ref + wait));
	*/
	
}

int get_ticks() { 
	return syscall(SYSCALL_GET_TICKS, 0, 0, 0, 0, 0);
}

char *
strtok(s, delim)
	register char *s;
	register const char *delim;
{
	register char *spanp;
	register int c, sc;
	char *tok;
	static char *last;


	if (s == NULL && (s = last) == NULL)
		return (NULL);

	/*
	 * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 */
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
		if (c == sc)
			goto cont;
	}

	if (c == 0) {		/* no non-delimiter characters */
		last = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
	for (;;) {
		c = *s++;
		spanp = (char *)delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				last = s;
				return (tok);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
}