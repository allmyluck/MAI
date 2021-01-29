CC = gcc

CFLAGS = -g  -Wextra  -pedantic -Werror  

OBJ = main.o 

main: main.o
	$(CC) $(CCFLAGS) -o main main.o -lpthread -lm

main.o: main.c

clean:
	@rm -r *.o main
