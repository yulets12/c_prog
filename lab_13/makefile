CC := gcc


CFLAGS := -std=c99 -Wall -Werror -g3 -pedantic




app.exe : main.o functions.o in_out.o
 
	$(CC) -o $@ $^



main.o : main.c functions.h in_out.h errors.h

	$(CC) $(CFLAGS) -ggdb -c main.c



in_out.o : in_out.c in_out.h errors.h

	$(CC) $(CFLAGS) -ggdb -c in_out.c



functions.o : functions.c functions.h in_out.h

	$(CC) $(CFLAGS) -ggdb -c functions.c



test.exe : test.o functions.o in_out.o
	$(CC) -o $@ $^



test.o : test.c functions.h in_out.h errors.h

	$(CC) $(CFLAGS) -c test.c



clean :

	$(RM) *.o *.exe
