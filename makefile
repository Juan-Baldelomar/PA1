all: main tests

tests:
	gcc -g -Wall -Wpedantic -lm tests.c arbolRN.c -o tests.app
	./tests.app 


main: 
	gcc -g -Wall -Wpedantic -lm main.c arbolRN.c -o main.app
	./main.app

clean:
	rm -rf *.app

