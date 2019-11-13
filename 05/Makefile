all: ser

ser: ser_main.o
	-@g++ -o ser ser_main.o --std=c++14

ser_main.o: ser_main.cpp serializer.h
	-@g++ -c ser_main.cpp --std=c++14

run:
	-@./ser

test:
	-@./ser

clean:
	-@rm -rf *.o
