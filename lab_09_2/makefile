CC := gcc


CFLAGS := -std=gnu99 -Wall -Werror -g3 -pedantic




app.exe : main.o functions.o
 
	$(CC) -o $@ $^



main.o : main.c functions.h errors.h

	$(CC) $(CFLAGS) -ggdb -c main.c



functions.o : functions.c functions.h
	$(CC) $(CFLAGS) -ggdb -c functions.c



test.exe : test.o functions.o
	$(CC) -o $@ $^



test.o : test.c functions.h errors.h

	$(CC) $(CFLAGS) -c test.c



clean :

	$(RM) *.o *.exe
