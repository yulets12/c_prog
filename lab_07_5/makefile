CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic


app.exe : main.o sort.o in_out.o filter.o 
	$(CC) -o $@ $^

main.o : main.c sort.h in_out.h filter.h errors.h
	$(CC) $(CFLAGS) -ggdb -c main.c

in_out.o : in_out.c in_out.h errors.h
	$(CC) $(CFLAGS) -ggdb -c in_out.c

sort.o : sort.c sort.h in_out.h
	$(CC) $(CFLAGS) -ggdb -c sort.c

filter.o : filter.c filter.h errors.h
	$(CC) $(CFLAGS) -ggdb -c filter.c

test.exe : test.o sort.o in_out.o filter.o
	$(CC) -o $@ $^

test.o : test.c sort.h in_out.h filter.h errors.h
	$(CC) $(CFLAGS) -c test.c

clean :
	$(RM) *.o *.exe
