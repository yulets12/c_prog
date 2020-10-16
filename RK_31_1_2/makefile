CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -g3


app.exe : main.o in_out.o
	$(CC) -o $@ $^

main.o : main.c in_out.h errors.h
	$(CC) $(CFLAGS) -ggdb -c main.c

in_out.o : in_out.c in_out.h errors.h
	$(CC) $(CFLAGS) -ggdb -c in_out.c

test.exe : test.o in_out.o
	$(CC) -o $@ $^

test.o : test.c errors.h in_out.h
	$(CC) $(CFLAGS) -ggdb -c test.c

clean:
	$(RM) *.exe *.o