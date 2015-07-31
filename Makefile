All: all
all: mem_eater
mem_eater:
	gcc -o mem_eater mem_eater.c -lpthread -lssl -lm -lcrypto
clean:
	rm -f mem_eater
