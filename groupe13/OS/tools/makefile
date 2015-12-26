# Compiler
CC=gcc
CFLAGS=-std=c99

# File system image
IMG=fs.img

# Tools
CREATE=pfscreate
ADD=pfsadd
DELETE=pfsdel
LIST=pfslist

# Creation arguments
BLOCK_SIZE=1024
FILE_ENTRIES=16
DATA_BLOCKS=128

# Add arguments
INPUT=example.txt

all:
	$(CC) $(CFLAGS) $(CREATE).c -o $(CREATE)
	$(CC) $(CFLAGS) $(ADD).c -o $(ADD)
	$(CC) $(CFLAGS) $(DELETE).c -o $(DELETE)
#	$(CC) $(CFLAGS) $(LIST).c -o $(LIST)

create: $(CREATE)
	clear
	./$(CREATE) $(IMG) $(BLOCK_SIZE) $(FILE_ENTRIES) $(DATA_BLOCKS)
	
add: $(ADD)
	clear
	./$(ADD) $(IMG) $(INPUT)

delete: $(DELETE)
	clear
	./$(DELETE) $(IMG) $(INPUT)
	
clean:
	rm $(IMG)
	