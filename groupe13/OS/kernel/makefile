ASMC=nasm
ASMFLAGS=-f elf32

CC=gcc
CFLAGS=-std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -c

MODE=normal

OBJS=bootloader.o kernel.o gdt.o gdt_asm.o idt.o idt_asm.o string.o periph.o io.o pic.o timer.o keyboard.o ide.o pfs.o syscall.o syscall_asm.o task_asm.o
KERNEL_DEPENDENCIES=

ifeq ($(MODE), test)
	CFLAGS += -D TEST
	OBJS += test.o
	KERNEL_DEPENDENCIES += test.h
endif

kernel.elf: $(OBJS)
	ld $^ -o $@ -Tkernel.ld -melf_i386

bootloader.o: bootloader.s
	$(ASMC) $< -o $@ $(ASMFLAGS)
	
kernel.o: kernel.c kernel.h ../common/types.h gdt.h idt.h ide.h pfs.h keyboard.h $(KERNEL_DEPENDENCIES)
	$(CC) $< -o $@ $(CFLAGS)

gdt.o: gdt.c gdt.h ../common/types.h x86.h string.h io.h task.h pfs.h
	$(CC) $< -o $@ $(CFLAGS)

gdt_asm.o: gdt_asm.s const.inc
	$(ASMC) $< -o $@ $(ASMFLAGS)
	
idt.o:	idt.c idt.h x86.h ../common/types.h io.h pic.h string.h timer.h keyboard.h
	$(CC) $< -o $@ $(CFLAGS)
	
idt_asm.o: idt_asm.s const.inc
	$(ASMC) $< -o $@ $(ASMFLAGS)

string.o: string.c string.h ../common/types.h
	$(CC) $< -o $@ $(CFLAGS)

periph.o: periph.s periph.h ../common/types.h
	$(ASMC) $< -o $@ $(ASMFLAGS)

io.o: io.c io.h ../common/types.h periph.h
	$(CC) $< -o $@ $(CFLAGS)
	
pic.o:	pic.c pic.h ../common/types.h periph.h io.h
	$(CC) $< -o $@ $(CFLAGS)
	
timer.o:	timer.c timer.h ../common/types.h periph.h io.h
	$(CC) $< -o $@ $(CFLAGS)
	
keyboard.o:	keyboard.c keyboard.h ../common/types.h x86.h periph.h io.h string.h
	$(CC) $< -o $@ $(CFLAGS)
	
test.o: test.c test.h ../common/types.h io.h periph.h kernel.h
	$(CC) $< -o $@ $(CFLAGS)

ide.o:	ide.c ide.h x86.h ../common/types.h io.h
	$(CC) $< -o $@ $(CFLAGS)

pfs.o:	pfs.c pfs.h ../common/types.h ide.h string.h io.h
	$(CC) $< -o $@ $(CFLAGS)
	
syscall.o:	syscall.c ../common/types.h ../common/syscall_nb.h io.h keyboard.h pfs.h timer.h
	$(CC) $< -o $@ $(CFLAGS)
	
syscall_asm.o:	syscall_asm.s const.inc
	$(ASMC) $< -o $@ $(ASMFLAGS)
	
task_asm.o:	task_asm.s
	$(ASMC) $< -o $@ $(ASMFLAGS)

clean:
	rm -f *.o kernel.elf
