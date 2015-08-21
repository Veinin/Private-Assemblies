.PHONY : clean all

CC = gcc
CFLAGS = -Wall -g -fPIC
LIB = ../unp.a

PROGS = echosrv echocli gethostinfo

all : $(PROGS)

echosrv : 
	$(CC) $(CFLAGS) -o $@ echosrv.c $(LIB)

echocli :
	$(CC) $(CFLAGS) -o $@ echocli.c $(LIB)

gethostinfo : 
	$(CC) $(CFLAGS) -o $@ gethostinfo.c $(LIB)

clean:
	rm -f $(PROGS)
