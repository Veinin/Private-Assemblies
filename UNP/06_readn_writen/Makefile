.PHONY : clean all

CC = gcc
CFLAGS = -Wall -g
LIB = ../unp.a

PROGS = echosrv echocli

all : $(PROGS)

echosrv : 
	$(CC) $(CFLAGS) -o $@ echosrv.c $(LIB)

echocli :
	$(CC) $(CFLAGS) -o $@ echocli.c $(LIB)

clean:
	rm -f $(PROGS)
