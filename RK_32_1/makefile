CC := gcc
CFLAGS := -std=gnu99 -Wall -Werror -pedantic -g3 -ggdb

app.exe : main.o in_out.o functions.o
	$(CC) $(CFLAGS) -o app.exe main.o in_out.o functions.o

main.o : main.c in_out.h functions.h
	$(CC) $(CFLAGS) -c main.c

in_out.o : in_out.c in_out.h
	$(CC) $(CFLAGS) -c in_out.c

functions.o : functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm *.o *.exe