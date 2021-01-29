CC = gcc

CFLAGS = -g -std=c99 -Wextra  -pedantic -Werror 

OBJ = main.o 

main: main.o
	$(CC) $(CCFLAGS) -o det main.o -lpthread

main.o: main.c

clean:
	@rm -r *.o det