// To avoid warnings if an argument is not used.
// Example:
// void f(int arg) {
//     UNUSED(arg);
// }

#include "../common/types.h"
#include "../common/syscall_nb.h"

#include "io.h"
#include "keyboard.h"
#include "pfs.h"

#define UNUSED(x) ((void)(x))

// System call handler: call the appropriate system call according to the nb argument.
// Called by the assembly code _syscall_handler
int syscall_handler(syscall_t nb, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t caller_tss_selector) {
	
	int ret = 0;
	switch (nb) {
		
		case SYSCALL_PUTC:
			print_char((char) arg1);
			break;
			
		case SYSCALL_PUTS:
			print_str((char*) arg1);
			break;
			
		case SYSCALL_EXEC:
			break;
			
		case SYSCALL_GETC:
			ret = getc();
			break;
			
		case SYSCALL_FILE_STAT:
			break;
			
		case SYSCALL_FILE_READ:
			break;
			
		case SYSCALL_FILE_REMOVE:
			break;
			
		case SYSCALL_FILE_ITERATOR:
			break;
			
		case SYSCALL_FILE_NEXT:
			break;
			
		case SYSCALL_GET_TICKS:
			break;
			
		default:
			break;
		
	}
	
	// End of routine
	return ret;
	
}

