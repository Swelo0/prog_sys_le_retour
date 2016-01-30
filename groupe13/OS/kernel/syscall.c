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
			ret = exec((char*)arg1);
			break;
			
		case SYSCALL_GETC:
			ret = getc();
			break;
			
		case SYSCALL_FILE_STAT:
			ret = file_stat((char*)arg1,(stat_t*)arg2);
			break;
			
		case SYSCALL_FILE_READ:
			ret = file_read((char*)arg1,(void*)arg2);
			break;
			
		case SYSCALL_FILE_REMOVE:
			ret = file_remove((char*)arg1);
			break;
			
		case SYSCALL_FILE_ITERATOR:
			ret = (int)file_iterator();
			break;
			
		case SYSCALL_FILE_NEXT:
			ret = file_next((char*)arg1,(file_iterator_t*)arg2);
			break;
			
		case SYSCALL_GET_TICKS:
			
			break;
			
		default:
			break;
		
	}
	
	// End of routine
	return ret;
	
}

