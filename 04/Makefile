all: bigint

bigint: BigInt.o main_bigint.o
	-@g++ -o bigint BigInt.o main_bigint.o --std=c++14

BigInt.o: BigInt.cpp BigInt.h
	-@g++ -c BigInt.cpp --std=c++14

main_bigint.o: main_bigint.cpp
	-@g++ -c main_bigint.cpp --std=c++14

run:
	-@./bigint

test:
	-@./bigint

clean:
	-@rm -rf *.o
