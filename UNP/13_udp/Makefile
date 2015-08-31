.PHONY : clean all

CC = gcc
CFLAGS = -Wall -g -fPIC
LIB = ../unp.a

PROGS = pollsrv pollcli

all : $(PROGS)

pollsrv : pollsrv.c
	$(CC) $(CFLAGS) -o $@ pollsrv.c $(LIB)

pollcli : pollcli.c
	$(CC) $(CFLAGS) -o $@ pollcli.c $(LIB)

clean:
	rm -f $(PROGS)
