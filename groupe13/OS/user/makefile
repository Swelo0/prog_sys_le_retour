ASMC=nasm
ASMFLAGS=-f elf32
CC=gcc
CFLAGS=-std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -c

APP=app

STUB=app_stub
LD=app.ld

OBJS=$(APP).o $(STUB).o

$(APP).elf:	$(OBJS)
	ld $^ -o $@ -T$(LD) -melf_i386
	
$(APP).o:	$(APP).c
	$(CC) $< -o $@ $(CFLAGS)

$(STUB).o:	$(STUB).s
	$(ASMC) $< -o $@ $(ASMFLAGS)
	
clean:
	rm *.o $(APP).elf