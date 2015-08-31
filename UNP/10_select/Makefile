.PHONY : clean all

CC = gcc
CFLAGS = -Wall -g -fPIC
LIB = ../unp.a

PROGS = selectsrv selectcli conntest

all : $(PROGS)

selectsrv : selectsrv.c
	$(CC) $(CFLAGS) -o $@ selectsrv.c $(LIB)

selectcli : selectcli.c
	$(CC) $(CFLAGS) -o $@ selectcli.c $(LIB)

conntest : conntest.c
	$(CC) $(CFLAGS) -o $@ conntest.c $(LIB)

clean:
	rm -f $(PROGS)
