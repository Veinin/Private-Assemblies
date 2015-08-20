.PHONY : clean all

CC = gcc
CFLAGS = -g 

LIB_DYNAMIC_NAME = ../unp.so
LIB_STATIC_NAME = ../unp.a
LIB_OBJS = readn.o writen.o readline.o

all : $(LIB_OBJS) 
	ar -rcs $(LIB_STATIC_NAME) $(LIB_OBJS)
	rm *.o

dynamic :
	$(CC) -shared -fPIC -o $(LIB_DYNAMIC_NAME) $(LIB_OBJS)

clean:
	rm -f *.o $(LIB_STATIC_NAME) $(LIB_DYNAMIC_NAME)
