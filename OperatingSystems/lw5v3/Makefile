CC = gcc
FLAGS = -g -Wall -Werror -Wextra

all: stt dnm

stt: mainstt.o libdeque.so 
	$(CC) $(FLAGS) -o stt mainstt.o -L. -ldeque -Wl,-rpath,.

dnm: maindnm.o libdeque.so
	$(CC) $(FLAGS) -rdynamic -o dnm maindnm.o -ldl

mainstt.o: mainstt.c 
	$(CC) -c $(FLAGS) mainstt.c

maindnm.o: maindnm.c 
	$(CC) -c $(FLAGS) maindnm.c	

libdeque.so: deque.o
	$(CC) $(FLAGS) -shared -o libdeque.so deque.o

deque.o: deque.c
	$(CC) -c -fPIC $(FLAGS) deque.c

clean:
	rm *.o stt dnm *.so