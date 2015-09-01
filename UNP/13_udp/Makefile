.PHONY : clean all

CC = gcc
CFLAGS = -Wall -g -fPIC
LIB = ../unp.a

PROGS = echosrv echocli

all : $(PROGS)

echosrv : echosrv.c
	$(CC) $(CFLAGS) -o $@ echosrv.c $(LIB)

echocli : echocli.c
	$(CC) $(CFLAGS) -o $@ echocli.c $(LIB)

clean:
	rm -f $(PROGS)
