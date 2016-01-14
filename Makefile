All: all
all: mem_eater
mem_eater:
	gcc -march=native -O3 -o mem_eater mem_eater.c -lpthread -lssl -lm -lcrypto
clean:
	rm -f mem_eater
