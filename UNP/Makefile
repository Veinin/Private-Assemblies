.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g

BIN=01_byteorder 02_addrconvert \
	03_echo_srv_cli/echosrv 03_echo_srv_cli/echocli \
	04_echo_srv_fork/echosrv \
	05_p2p_srv_cli/p2p_srv 05_p2p_srv_cli/p2p_cli \
	06_readn_writen/echosrv 06_readn_writen/echocli \

all:$(BIN)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)
