#include "ulibc.h"

int read_file(char* filename, uchar* buf) { 
	return syscall(SYSCALL_FILE_READ, filename, buf, 0, 0, 0);
}

int get_stat(char* filename, stat_t* stat) { 
	return syscall(SYSCALL_FILE_STAT, filename, stat, 0, 0, 0);
}

int remove_file(char* filename) { 
	return syscall(SYSCALL_FILE_REMOVE, filename, 0, 0, 0, 0);
}

file_iterator_t get_file_iterator(){  
	return syscall(SYSCALL_FILE_ITERATOR, 0, 0, 0, 0, 0);
}

int get_next_file(char* filename, file_iterator_t* it) { 
	return syscall(SYSCALL_FILE_NEXT, 0, 0, 0, 0, 0);
}

int exec(char* filename){ 
	return syscall(SYSCALL_EXEC, filename, 0, 0, 0, 0);
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
        s = (k<<3)+(k<<1)+(*s)-'0';
        s++;
    }
    return k;
}

int getc() { 
	return syscall(SYSCALL_GETC, 0, 0, 0, 0, 0);
}

void putc(char c) {
	return syscall(SYSCALL_PUTC, c, 0, 0, 0, 0);
}

void puts(char* str) { 
	return syscall(SYSCALL_PUTS, str, 0, 0, 0, 0);
}

void print_int(int32_t n)
{
    if (n < 0)
    {
        pputc('-');
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
        putc(char)(unit + 55));
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

	// Ticks à attendre
	uint wait = (1193180 / frequence_divise) * (ms / 1000);
	// Référence
	uint ref = ticks;
	// Boucle
	while (get_ticks() <= (ref + wait));
	
}

int get_ticks() { 
	return syscall(SYSCALL_GET_TICKS, 0, 0, 0, 0, 0);
}