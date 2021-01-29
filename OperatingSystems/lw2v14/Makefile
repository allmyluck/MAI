CC = gcc

CFLAGS = -g -std=c99 -Wextra  -pedantic -Werror -lm

OBJ = main.o 

main: l2v14.o
	$(CC) $(CCFLAGS) -o main l2v14.o -lm 

l2v14.o: l2v14.c

clean:
	@rm -r *.o main