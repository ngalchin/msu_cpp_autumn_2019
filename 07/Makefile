all: vect

vect: main_tests.o
	-@g++ -o vect main_tests.o --std=c++14

main_tests.o: main_tests.cpp myvect.h
	-@g++ -c main_tests.cpp --std=c++14

run:
	-@./vect

test:
	-@./vect

clean:
	-@rm -rf *.o
