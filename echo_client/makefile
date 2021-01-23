client: echoclient.o csapp.o
	gcc -o client echoclient.o csapp.o -lpthread
csapp.o: csapp.c csapp.h
	gcc -c csapp.c csapp.h
echoclient.o: csapp.h echoclient.c
	gcc -c csapp.h echoclient.c

