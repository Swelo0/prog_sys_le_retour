# Compiler
CC=gcc
CFLAGS=-std=c99 -Wall

# Tools
CREATE=pfscreate
ADD=pfsadd
DEL=pfsdel
LIST=pfslist

all:
	$(CC) $(CFLAGS) $(CREATE).c -o $(CREATE)
	$(CC) $(CFLAGS) $(ADD).c    -o $(ADD)
	$(CC) $(CFLAGS) $(DEL).c    -o $(DEL)
	$(CC) $(CFLAGS) $(LIST).c   -o $(LIST)

clean:
	rm $(CREATE) $(ADD) $(DEL) $(LIST)
	