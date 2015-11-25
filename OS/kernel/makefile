ASMC=nasm
ASMFLAGS=-f elf32

CC=gcc
CFLAGS=-std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -c

MODE=normal

OBJS=bootloader.o kernel.o gdt.o gdt_asm.o idt.o idt_asm.o string.o periph.o io.o pic.o
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
	
kernel.o: kernel.c kernel.h gdt.h idt.h io.h ../common/types.h $(KERNEL_DEPENDENCIES)
	$(CC) $< -o $@ $(CFLAGS)

gdt.o: gdt.c gdt.h ../common/types.h x86.h string.h
	$(CC) $< -o $@ $(CFLAGS)

gdt_asm.o: gdt_asm.s const.inc
	$(ASMC) $< -o $@ $(ASMFLAGS)
	
idt.o:	idt.c idt.h io.h pic.h string.h x86.h ../common/types.h
	$(CC) $< -o $@ $(CFLAGS)
	
idt_asm.o: idt_asm.s const.inc
	$(ASMC) $< -o $@ $(ASMFLAGS)

string.o: string.c string.h ../common/types.h
	$(CC) $< -o $@ $(CFLAGS)

periph.o: periph.s periph.h ../common/types.h
	$(ASMC) $< -o $@ $(ASMFLAGS)

io.o: io.c io.h ../common/types.h periph.h
	$(CC) $< -o $@ $(CFLAGS)
	
pic.o:	pic.c pic.h ../common/types.h string.h
	$(CC) $< -o $@ $(CFLAGS)
	
test.o: test.c test.h io.h periph.h ../common/types.h
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -f *.o kernel.elf

