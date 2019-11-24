all: format

format: format_main.o
	-@g++ -o format format_main.o --std=c++14

format_main.o: format_main.cpp format.h
	-@g++ -c format_main.cpp --std=c++14

run:
	-@./format

test:
	-@./format

clean:
	-@rm -rf *.o
