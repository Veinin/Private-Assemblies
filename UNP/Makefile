.PHONY : clean all

CC = gcc
CFLAGS = -Wall -g
LIB = unp.so

BIN = 01_byteorder 02_addrconvert \
	03_echo_srv_cli/echosrv 03_echo_srv_cli/echocli \
	04_echo_srv_fork/echosrv \
	05_p2p_srv_cli/p2p_srv 05_p2p_srv_cli/p2p_cli \

all : $(BIN)

clean:
	rm -f *.o $(BIN)
