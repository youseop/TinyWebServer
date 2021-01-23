server: echoserveri.o csapp.o
	gcc -o server echoserveri.o csapp.o -lpthread
csapp.o: csapp.c csapp.h
	gcc -c csapp.c csapp.h
echoserveri.o: csapp.h echoserveri.c
	gcc -c csapp.h echoserveri.c

