all: allocator

allocator: linear_allocator.o allocator_main.o
	-@g++ -o allocator linear_allocator.o allocator_main.o --std=c++14

linear_allocator.o: linear_allocator.cpp linear_allocator.h
	-@g++ -c linear_allocator.cpp --std=c++14

allocator_main.o: allocator_main.cpp
	-@g++ -c allocator_main.cpp --std=c++14

run:
	-@./allocator

clean:
	-@rm -rf *.o
