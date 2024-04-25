#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -g -Wno-unused-parameter
CC = gcc

PROGRAMS = tests_ecosys2 tests_ecosys ecosys hello_world2.h

.PHONY:	all clean

all: $(PROGRAMS)

hello_world2.o: afficheur.c
	gcc $(CFLAGS) -c afficheur.c

ecosys.o: ecosys.c
	gcc $(CFLAGS) -c ecosys.c

main_ecosys.o: main_ecosys.c 
	gcc $(CFLAGS) -c main_ecosys.c

main_tests2.o: main_tests2.c
	gcc $(CFLAGS) -c main_tests2.c

main_tests.o: main_tests.c
	gcc $(CFLAGS) -c main_tests.c

tests_ecosys: ecosys.o main_tests.o
	$(CC) -o $@ $(CFLAGS) $^

ecosys: ecosys.o main_ecosys.o afficheur.o
	$(CC) -o $@ $(CFLAGS) $^

tests_ecosys2: ecosys.o main_tests2.o
	$(CC) -o $@ $(CFLAGS) $^


#Ou plus simplement
#%.o:%.c %.h
#	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)
