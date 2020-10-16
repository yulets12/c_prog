CC := gcc


CFLAGS := -std=c99 -Wall -Werror -g3 -pedantic




app.exe : main.o operations.o in_out.o
 
	$(CC) -o $@ $^



main.o : main.c operations.h in_out.h errors.h

	$(CC) $(CFLAGS) -ggdb -c main.c



in_out.o : in_out.c in_out.h errors.h

	$(CC) $(CFLAGS) -ggdb -c in_out.c



operations.o : operations.c operations.h in_out.h

	$(CC) $(CFLAGS) -ggdb -c operations.c



test.exe : test.o operations.o in_out.o
	$(CC) -o $@ $^



test.o : test.c operations.h in_out.h errors.h

	$(CC) $(CFLAGS) -c test.c



clean :

	$(RM) *.o *.exe
