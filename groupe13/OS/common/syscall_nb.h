#ifndef _SYSCALL_NB_H_
#define _SYSCALL_NB_H_

typedef enum { 

    SYSCALL_PUTC          = 0,
    SYSCALL_PUTS          = 1,
    SYSCALL_EXEC          = 2,
    SYSCALL_GETC          = 3,
    SYSCALL_FILE_STAT     = 4,
    SYSCALL_FILE_READ     = 5,
    SYSCALL_FILE_REMOVE   = 6,
    SYSCALL_FILE_ITERATOR = 7,
    SYSCALL_FILE_NEXT     = 8,
    SYSCALL_GET_TICKS     = 9,
	
    __SYSCALL_END__
	
} syscall_t;

#endif
