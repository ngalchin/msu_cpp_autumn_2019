all: sort

sort: main.o
	-@g++ -pthread -o sort main.o --std=c++14

main.o: main.cpp
	-@g++ -c main.cpp --std=c++14

run:
	-@./sort

test:
	-@./sort

clean:
	-@rm -rf *.o
