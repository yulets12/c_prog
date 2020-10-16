CC := gcc


CFLAGS := -std=gnu99 -Wall -Werror -g3 -pedantic




test.exe : test.o functions.o
	$(CC) -o $@ $^


functions.o : functions.c functions.h
	$(CC) $(CFLAGS) -ggdb -c functions.c



test.o : test.c functions.h 
	$(CC) $(CFLAGS) -ggdb -c test.c



clean :

	$(RM) *.o *.exe
