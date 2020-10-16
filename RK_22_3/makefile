CC := gcc
OBJS := in_out.o process.o
FLAGS := -std=c99 -Wall -Werror -pedantic

main.exe : main.o $(OBJS)
	$(CC) -o main.exe main.o $(OBJS)
	
test.exe : test.o process.o
	$(CC) -o test.exe test.o process.o
	
in_out.o : in_out.c err.h in_out.h
	$(CC) $(FLAGS) -c in_out.c
	
process.o : process.c err.h process.h
	$(CC) $(FLAGS) -c process.c
	
main.o : main.c err.h in_out.h process.h
	$(CC) $(FLAGS) -c main.c

test.o : test.c err.h process.h
	$(CC) $(FLAGS) -c test.c 
	
clean : 
	$(RM) *.o *.exe