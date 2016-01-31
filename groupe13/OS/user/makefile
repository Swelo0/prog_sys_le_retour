ASMC=nasm
ASMFLAGS=-f elf32
CC=gcc
CFLAGS=-std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -c

APP=app
LIB=ulibc
CALL=syscall

STUB=app_stub
LD=app.ld

OBJS=$(APP).o $(STUB).o $(LIB).o $(CALL).o shell.o

$(APP).elf:	$(OBJS)
	ld $^ -o $@ -T$(LD) -melf_i386
	
$(APP).o:	$(APP).c shell.h
	$(CC) $< -o $@ $(CFLAGS)

$(STUB).o:	$(STUB).s
	$(ASMC) $< -o $@ $(ASMFLAGS)
	
$(LIB).o: $(LIB).c $(LIB).h
	$(CC) $< -o $@ $(CFLAGS)
	
$(CALL).o:	$(CALL).s
	$(ASMC) $< -o $@ $(ASMFLAGS)
	
shell.o:	shell.c shell.h
	$(CC) $< -o $@ $(CFLAGS)
	
clean:
	rm *.o $(APP).elf