OBJECTS = 20111593.o
CC = gcc

main : $(OBJECTS) 20111593.h
	$(CC) -o 20111593.out $(OBJECTS) -Wall

20111593.o : 20111593.c 20111593.h
	$(CC) -c 20111593.c -Wall

clear :
	rm $(OBJECTS) 20111593.out output.txt
