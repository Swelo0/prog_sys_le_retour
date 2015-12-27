# Compiler
CC=gcc
CFLAGS=-std=c99 -Wall

# File system image
IMG=fs.img
# Input file
INPUT=example.txt

# Tools
CREATE=pfscreate
ADD=pfsadd
DEL=pfsdel
LIST=pfslist

# Creation arguments
BLOCK_SIZE=1024
FILE_ENTRIES=16
DATA_BLOCKS=128

all:
	$(CC) $(CFLAGS) $(CREATE).c -o $(CREATE)
	$(CC) $(CFLAGS) $(ADD).c    -o $(ADD)
	$(CC) $(CFLAGS) $(DEL).c    -o $(DEL)
	$(CC) $(CFLAGS) $(LIST).c   -o $(LIST)

create: $(CREATE)
	clear
	./$(CREATE) $(IMG) $(BLOCK_SIZE) $(FILE_ENTRIES) $(DATA_BLOCKS)
	
add: $(ADD)
	clear
	./$(ADD) $(IMG) $(INPUT)

delete: $(DEL)
	clear
	./$(DEL) $(IMG) $(INPUT)

list: $(LIST)
	clear
	./$(LIST) $(IMG)
	
clean:
	rm $(IMG)
	