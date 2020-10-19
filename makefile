all: tests main memcheck clean

tests:
	gcc -g -Wall -Wpedantic -lm tests.c arbolRN.c -o tests.app
	./tests.app 


main: 
	gcc -g -Wall -Wpedantic -lm main.c arbolRN.c -o main.app
	./main.app

memcheck:
	valgrind ./tests.app
	valgrind ./main.app

clean:
	rm -rf *.app

