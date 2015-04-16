Libunp = ../libunp.a

all : tcpserver01 tcpcli01 tcpserver02 tcpcli02
	@echo "Compile finished..."

tcpserver01 : $(Libunp)
	cc -o tcpserver01 $(Libunp) tcpserver01.c

tcpcli01 : $(Libunp)
	cc -o tcpcli01 $(Libunp) tcpcli01.c

tcpserver02 : $(Libunp)
	cc -o tcpserver02 $(Libunp) tcpserver02.c

tcpcli02 : $(Libunp)
	cc -o tcpcli02 $(Libunp) tcpcli02.c

.PHONY : clean
clean :
	-rm tcpserver01 tcpcli01 tcpserver02 tcpcli02
	@echo "Clean successful..."