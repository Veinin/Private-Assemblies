.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g

BIN=01_byteorder 02_addrconvert
all:$(BIN)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)
