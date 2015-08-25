.PHONY : clean all

CC = gcc
CFLAGS = -Wall -g -fPIC
LIB = ../unp.a

PROGS = echosrv echocli gethostinfo

all : $(PROGS)

echosrv : echosrv.c
	$(CC) $(CFLAGS) -o $@ echosrv.c $(LIB)

echocli : echocli.c
	$(CC) $(CFLAGS) -o $@ echocli.c $(LIB)

gethostinfo : gethostinfo.c 
	$(CC) $(CFLAGS) -o $@ gethostinfo.c $(LIB)

clean:
	rm -f $(PROGS)
