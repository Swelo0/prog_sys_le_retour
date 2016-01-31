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
#include "timer.h"
#include "gdt.h"

#define UNUSED(x) ((void)(x))

// System call handler: call the appropriate system call according to the nb argument.
// Called by the assembly code _syscall_handler
int syscall_handler(syscall_t nb, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t caller_tss_selector) {
	
	printf("task %d called syscall_handler\n", caller_tss_selector);
	
	// Offset for pointers to reach the real address (task thinks it indexes since 0x0 but it really doesn't)
	task_t* t = get_task(caller_tss_selector);
	uint32_t offset = FIRST_TASK + t.gdt_tss_sel * TASK_LIMIT;
	
	int ret = 0;
	switch (nb) {
		
		case SYSCALL_PUTC:
			UNUSED(arg2);
			UNUSED(arg3);
			UNUSED(arg4);
			print_char((char) arg1 + offset);
			break;
			
		case SYSCALL_PUTS:
			UNUSED(arg2);
			UNUSED(arg3);
			UNUSED(arg4);
			print_str((char*) arg1 + offset);
			break;
			
		case SYSCALL_EXEC:
			UNUSED(arg2);
			UNUSED(arg3);
			UNUSED(arg4);
			ret = exec((char*) arg1 + offset);
			break;
			
		case SYSCALL_GETC:
			UNUSED(arg1);
			UNUSED(arg2);
			UNUSED(arg3);
			UNUSED(arg4);
			ret = getc();
			break;
			
		case SYSCALL_FILE_STAT:
			UNUSED(arg3);
			UNUSED(arg4);
			ret = file_stat((char*) arg1 + offset, (stat_t*) arg2 + offset);
			break;
			
		case SYSCALL_FILE_READ:
			UNUSED(arg3);
			UNUSED(arg4);
			ret = file_read((char*) arg1 + offset, (void*) arg2 + offset);
			break;
			
		case SYSCALL_FILE_REMOVE:
			UNUSED(arg2);
			UNUSED(arg3);
			UNUSED(arg4);
			ret = file_remove((char*) arg1 + offset);
			break;
			
		case SYSCALL_FILE_ITERATOR:
			UNUSED(arg2);
			UNUSED(arg3);
			UNUSED(arg4);
			file_iterator_t it = file_iterator();
			arg1 = (uint32_t) &it + offset;
			break;
			
		case SYSCALL_FILE_NEXT:
			UNUSED(arg3);
			UNUSED(arg4);
			ret = file_next((char*) arg1 + offset, (file_iterator_t*) arg2 + offset);
			break;
			
		case SYSCALL_GET_TICKS:
			UNUSED(arg1);
			UNUSED(arg2);
			UNUSED(arg3);
			UNUSED(arg4);
			ret = get_ticks();
			break;
			
		default:
			UNUSED(nb);
			UNUSED(arg1);
			UNUSED(arg2);
			UNUSED(arg3);
			UNUSED(arg4);
			break;
		
	}
	
	// End of routine
	return ret;
	
}