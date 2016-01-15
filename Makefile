All: all
all: mem_eater
mem_eater:
	gcc -march=native -O3 -o mem_eater mem_eater.c -lpthread
clean:
	rm -f mem_eater
