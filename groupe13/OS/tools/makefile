# Compiler
CC=gcc

# File system image
IMG=fs.img

# Tools
CREATE=pfscreate
ADD=pfsadd
DELETE=pfsdel
LIST=pfslist

# Arguments
BLOCK_SIZE=1024
FILE_ENTRIES=1
DATA_BLOCKS=64

all:
	$(CC) $(CREATE).c -o $(CREATE)
#	$(CC) $(ADD).c -o $(ADD)
#	$(CC) $(DELETE).c -o $(DELETE)
#	$(CC) $(LIST).c -o $(LIST)

create: $(CREATE)
	./$(CREATE) $(IMG) $(BLOCK_SIZE) $(FILE_ENTRIES) $(DATA_BLOCKS)
	
look: $(IMG)
	hexdump $(IMG)
	
clean:
	rm $(IMG) $(CREATE)
	