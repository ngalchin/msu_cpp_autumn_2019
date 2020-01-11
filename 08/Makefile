all: pool

pool: main.o
	-@g++ -pthread -o pool main.o --std=c++11

main.o: main.cpp thread_pool.h
	-@g++ -c main.cpp --std=c++11

run:
	-@./pool

test:
	-@./pool

clean:
	-@rm -rf *.o
